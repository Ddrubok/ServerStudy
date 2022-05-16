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


//template<typename T>
//class LockFreeStack
//{
//	struct Node
//	{
//		Node(const T& value) :data(make_shared<T>(value)),next(nullptr)
//		{
//
//		}
//
//		shared_ptr<T> data; 
//		shared_ptr<Node> next;
//
//	};
//
//public:
//	void Push(const T& value)
//	{
//
//		shared_ptr<Node> node = make_shared<Node>(value);
//
//		node->next = std::atomic_load(&_head);
//
//		while (std::atomic_compare_exchange_weak(&_head, &node->next, node) == false)
//		{
//
//		}
//	}
//
//	shared_ptr<T> TryPop()
//	{
//		shared_ptr<Node> oldHead = std::atomic_load(&_head);
//
//		while (oldHead && std::atomic_compare_exchange_weak(&_head, &oldHead, oldHead->next) == false)
//		{
//
//		}
//
//		if (oldHead == nullptr)
//			return shared_ptr<T>();
//
//		return oldHead->data;
//
//	}
//
//	
//
//private:
//	shared_ptr<Node> _head;
//};

template<typename T>
class LockFreeStack
{
	struct Node;
	struct CountedNodePtr
	{
		int32 externalCount = 0;
		Node* ptr = nullptr;
	};

	struct Node
	{
		Node(const T& value) :data(make_shared<T>(value))
		{

		}

		shared_ptr<T> data;
		atomic<int32> internalCount = 0;
		CountedNodePtr next;

	};



public:
	void Push(const T& value)
	{
		CountedNodePtr node;
		node.ptr = new Node(value);
		node.externalCount = 1;

		node.ptr->next = _head;

		while (_head.compare_exchange_weak(node.ptr->next, node) == false)
		{

		}


	}

	shared_ptr<T> TryPop()
	{

		CountedNodePtr oldHead = _head;
		while (true)
		{
			//참조권 획득
			IncreaseHeadCount(oldHead);

			//최소한 externalCount >=2 일테니 삭제 x (안전하게 접근할 수 있는)

			Node* ptr = oldHead.ptr;

			if (ptr == nullptr)
				return shared_ptr<T>();

			//소유권 흭득 (ptr->next 로 head를 바꿔치기 한 얘가 이김)

			if (_head.compare_exchange_strong(oldHead, ptr->next))
			{
				shared_ptr<T> res;
				res.swap(ptr->data);
				const int32 countIncrease = oldHead.externalCount - 2;

				if (ptr->internalCount.fetch_add(countIncrease) == -countIncrease)
					delete ptr;

				return res;
			}
			else if (ptr->internalCount.fetch_sub(1) == 1)
			{
				//참조권은 얻었으나, 소유권은 실패 ->뒷수습은 내가한다.
				delete ptr;
			}
		}
	}


private:
	void IncreaseHeadCount(CountedNodePtr& oldCounter)
	{
		while (true)
		{
			CountedNodePtr newCounter = oldCounter;
			newCounter.externalCount++;

			if (_head.compare_exchange_strong(oldCounter, newCounter))
			{
				oldCounter.externalCount = newCounter.externalCount;
				break;
			}
		}

	}

private:
	atomic<CountedNodePtr> _head;
};
