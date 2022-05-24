#pragma once
class AccountManager
{
	USE_LOCK;

public:
	void AccountThenPlyer();
	void Lock();

};

extern AccountManager GAccountManager;
