#include<iostream>
#include<memory>
#include<time.h>
#include"Logger.h"


using namespace std;


CLogger* pLog;

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	pLog = new CLogger("Test");

	if (pLog)
	{
		pLog->Start();
		pLog->debug("日志记录线程启动....");
	}

	while (true)
	{
		int rr = rand() % 4 + 1;
		switch (rr)
		{
		case 1:
			pLog->info("info信息");
			break;
		case 2:
			pLog->debug("debug信息");
			break;
		case 3:
			pLog->warning("waring信息");
			break;
		case 4:
			pLog->error("error信息");
			break;
		default:
			break;
		}
		Sleep(1000);
	}

	delete pLog;

	system("pause");
	return 0;
}