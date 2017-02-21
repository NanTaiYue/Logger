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
		pLog->debug("��־��¼�߳�����....");
	}

	while (true)
	{
		int rr = rand() % 4 + 1;
		switch (rr)
		{
		case 1:
			pLog->info("info��Ϣ");
			break;
		case 2:
			pLog->debug("debug��Ϣ");
			break;
		case 3:
			pLog->warning("waring��Ϣ");
			break;
		case 4:
			pLog->error("error��Ϣ");
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