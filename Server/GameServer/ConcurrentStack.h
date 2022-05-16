#pragma once
#include<mutex>

template<typename T>
class LockStack
{
public:
	LockStack() {}

	LockStack(const LockStack&) = delete;
	LockStack& operator = (const LockStack&) = delete;

	void Push(T value)
	{
		lock_guard<mutex> lock(_mutex);
		_stack.push(std::move(value));
	}

	bool TryPop(T& value)
	{
		lock_guard<mutex> lock(_mutex);
		if (_stack.empty())
			return false;

		value = std::move(stack.top());
		_stack.pop();
		return true;
	}

	void WaitPop(T& value)
	{
		unique_lock<mutex> lock(_mutex);
		_condVar.wait(lock, [this] {return _stack.empty() == false; });
		value = std::move(_stack.top());
		_stack.pop();
	}

private:
	stack<T> _stack;
	mutex _mutex;
	condition_variable _condVar;
};


template<typename T>
class LockFreeStack
{
	struct Node
	{
		Node(const T& value) : data(value)
		{

		}
		T data;
		Node* next;

	};

public:
	void Push(const T& value)
	{
		Node* node = new Node(value);
		node->next = _head;

		while (_head.compare_exchange_weak(node->next, node) == false)
		{

		}
		_head = node;
	}

	//1) head �б�
	//2) head->next �б�
	//3) head = head->next
	//4) data �����ؼ� ��ȯ
	//5) ������ ��带 ����

	bool TryPop(T& value)
	{
		++_popCount;

		Node* oldHead = _head;


		while (oldHead && _head.compare_exchange_weak(oldHead, oldHead->next)==false)
		{

		}

		if (oldHead == nullptr)
		{
			--_popCount;
			return false;
		}
		else
		{
			value = oldHead->data;

			TryDelete(oldHead);

			return true;

		}
	}

	//1) ������ �и�
	//2) ī���� üũ
	//3) ��ȥ�ڸ� ����

	void TryDelete(Node* oldHead)
	{
		//�� �ܤӿ� �ֳ�?

		if (_popCount == 1)
		{
			// �� ȥ����
			
			//�̿� ȥ���ΰ� ���� ����� �ٸ� �����͵鵵 �����غ���.
			Node* node = _pendingList.exchange(nullptr);

			if (--_popCount == 0)
			{
				//�߰��� ����� �갡 ����
				//����� ������� �и���
				DeleteNode(node);
			}

			//so �� ������ ����
			delete oldHead;
		}
		else
		{
			//���� �������� �ٽ� ���� ���ƾ���.
		}
	}

	void ChainPendingNodeList(Node* first, Node* last)
	{

	}

	static void DeletNodes(Node* node)
	{
		while (node)
		{
			Node* next = node->next;
			delete node;
			node = next;
		}
	}

private:
	atomic<Node*> _head;

	atomic<uint32> _popCount = 0;//pop�� �������� ������ ����


	atomic<Node*> _pendingList // �����Ǿ���� ����
};
