#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<atomic>
#include <mutex>
#include<windows.h>
#include<future>
#include <ThreadManager.h>
#include <CoreMacro.h>

#include "PlayerManager.h"
#include "AccountManager.h"



int main()
{
	GThreadManager->Launch([=]
		{
			while (true)
			{
				cout << "PlayerThenAccount" << endl;
				GPlayerManager.PlayerThenAccount();
				this_thread::sleep_for(100ms);
			}

		});

	GThreadManager->Launch([=]
		{
			while (true)
			{
				cout << "AccountThenPlayer" << endl;
				GAccountManager.AccountThenPlyer();
				this_thread::sleep_for(100ms);
			}

		});
	GThreadManager->Join();
	return 0;
}