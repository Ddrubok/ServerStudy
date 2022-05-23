#include "pch.h"
#include "DeadLockProfiler.h"

//DeadLockProfiler

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard guard(_lock);

	int32 lockId = 0;

	auto findIt = _nameTold.find(name);

	if (findIt == _nameTold.end())
	{
		lockId = static_cast<int32>(_nameTold.size());
		_nameTold[name] = lockId;
		_idToName[lockId] = name;
	}
	else
	{
		lockId = findIt->second;
	}

	if (_lockStack.empty() == false)
	{
		const int32 prevId = _lockStack.top();

		if (lockId != prevId)
		{
			set<int32>& history = _lockHistory[prevId];

			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}

	}

	_lockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(_lock);

	if (_lockStack.empty())
	{
		CRASH("multiple_unlock");
	}

	int32 lockId = _nameTold[name];
	if (_lockStack.top() != lockId)
	{
		CRASH("invalid_unlcok");
	}

	_lockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const int32 lockCount = static_cast<int32>(_nameTold.size());
	_discoveredOrder = vector<int32>(lockCount, -1);
	_discoveredCount = 0;
	_finished = vector<bool>(lockCount, false);
	_parent = vector<int32>(lockCount, -1);

	for (int32 lockId = 0; lockId < lockCount; lockId++)
		Dfs(lockId);

	_discoveredOrder.clear();
	_finished.clear();
	_parent.clear();
}

void DeadLockProfiler::Dfs(int32 here)
{
	if (_discoveredOrder[here] != -1)
		return;

	_discoveredOrder[here] = _discoveredCount++;

	auto findIt = _lockHistory.find(here);

	if (findIt == _lockHistory.end())
	{
		_finished[here] = true;
		return;
	}

	set<int32>& nextSet = findIt->second;

	for (int32 there : nextSet)
	{
		if (_discoveredOrder[there] == -1)
		{
			_parent[there] = here;
			Dfs(there);
			continue;
		}

		if (_discoveredOrder[here] < _discoveredOrder[there])
			continue;

		if (_finished[there] == false)
		{
			printf("%s -> %s\n", _idToName[here], _idToName[there]);

			int32 now = here;

			while (true)
			{
				printf("%s -> %s\n", _idToName[_parent[now]], _idToName[now]);

				now = _parent[now];

				if (now == there)
					break;
			}
			CRASH("DeadLock_Detected");
		}
	}

	_finished[here] = true;
}
