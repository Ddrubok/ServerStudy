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
		Node(const T& value) : data(make_shared<T>(value), next(nullptr)
		{

		}

		shared_ptr<T> data;
		shared_ptr<Node>next;

	};

public:
	void Push(const T& value)
	{
		Node* node = new Node(value);
		node->next = _head;

		while (_head.compare_exchange_weak(node->next, node) == false)
		{
		}
	}

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

	void TryDelete(Node* oldHead)
	{
		

		if (_popCount == 1)
		{
			
			Node* node = _pendingList.exchange(nullptr);

			if (--_popCount == 0)
			{
				
				DeletNodes(node);
			}
			else if(node)
			{
				ChainPendingNodeList(node);
			}

			
			delete oldHead;
		}
		else
		{
			
			ChainPendingNodeList(oldHead);
			--_popCount;
		}
	}

	void ChainPendingNodeList(Node* first, Node* last)
	{
		last->next = _pendingList;

		while (_pendingList.compare_exchange_weak(last->next, first) == false)
		{
		}
	}

	void ChainPendingNodeList(Node* node)
	{
		Node* last = node;
		while (last->next)
			last = last->next;

		ChainPendingNodeList(node, last);
	}

	void ChainPendingNode(Node* node)
	{
		ChainPendingNodeList(node, node);
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

	atomic<uint32> _popCount = 0;//pop을 실행중인 쓰레드 개수


	atomic<Node*> _pendingList; // 삭제되어야할 노드들
};
