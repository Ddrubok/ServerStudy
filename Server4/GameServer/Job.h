#pragma once
class IJob
{
public:
	virtual void Execute(){}
};

class HealJob :IJob
{
public:
	virtual void Execute() override
	{

		cout << _target << "ÇÑÅ× Èú " << _healValue << "¸¸Å­ ÁÜ";
	}

public:
	uint64 _target = 0;
	uint32 _healValue = 0;
};
using JobRef = shared_ptr<IJob>;

class JobQueue
{
public:
	void Push(JobRef job)
	{
		WRITE_LOCK;
		_jobs.push(job);
	}

	JobRef Pop()
	{
		WRITE_LOCK;
		JobRef _ref = _jobs.front();
		_jobs.pop();
		return _ref;
	}

private:
	USE_LOCK;
	queue<JobRef> _jobs;

};