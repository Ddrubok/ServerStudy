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

	//1) head 읽기
	//2) head->next 읽기
	//3) head = head->next
	//4) data 추출해서 반환
	//5) 추출한 노드를 삭제

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

	//1) 데이터 분리
	//2) 카운터 체크
	//3) 나혼자면 삭제

	void TryDelete(Node* oldHead)
	{
		//나 외ㅣ에 있나?

		if (_popCount == 1)
		{
			// 나 혼자임
			
			//이왕 혼자인거 삭제 예약된 다른 데이터들도 삭제해보자.
			Node* node = _pendingList.exchange(nullptr);

			if (--_popCount == 0)
			{
				//중간에 끼어든 얘가 없음
				//끼어들어도 상관없음 분리됨
				DeleteNode(node);
			}

			//so 내 데이터 삭제
			delete oldHead;
		}
		else
		{
			//누가 끼어들었음 다시 갖다 놓아야함.
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

	atomic<uint32> _popCount = 0;//pop을 실행중인 쓰레드 개수


	atomic<Node*> _pendingList // 삭제되어야할 노드들
};
