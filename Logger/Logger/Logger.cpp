#include "Logger.h"

CLogger::CLogger()
	:pFile(NULL)
{
	m_bIsRunning = true;
	init();
}

CLogger::CLogger(string _name)
	:m_logName(_name)
	,pFile(NULL)
{
	m_bIsRunning = true;
	init();
}

CLogger::~CLogger()
{
}

void CLogger::info(const char * format, ...)
{
	if (!m_bIsRunning) return;

	LOG_MSG msg;
	msg._level = LOG_LEVEL::LOG_LEVEL_INFO;

	ConstructMsg(&msg, format);
	{
		CGuard guard(&m_cs);
		m_MsgDeque.push_back(msg);
	}
}

void CLogger::debug(const char * format, ...)
{
	if (!m_bIsRunning) return;

	LOG_MSG msg;
	msg._level = LOG_LEVEL::LOG_LEVEL_DEBUG;

	ConstructMsg(&msg, format);
	{
		CGuard guard(&m_cs);
		m_MsgDeque.push_back(msg);
	}
}

void CLogger::warning(const char * format, ...)
{
	if (!m_bIsRunning) return;

	LOG_MSG msg;
	msg._level = LOG_LEVEL::LOG_LEVEL_WARNING;

	ConstructMsg(&msg, format);
	{
		CGuard guard(&m_cs);
		m_MsgDeque.push_back(msg);
	}
}

void CLogger::error(const char * format, ...)
{
	if (!m_bIsRunning) return;

	LOG_MSG msg;
	msg._level = LOG_LEVEL::LOG_LEVEL_ERROR;

	ConstructMsg(&msg, format);
	{
		CGuard guard(&m_cs);
		m_MsgDeque.push_back(msg);
	}
}


unsigned int CLogger::Run()
{
	while (m_bIsRunning)
	{
		deque<LOG_MSG> tmpDeque;
		{
			CGuard guard(&m_cs);
			tmpDeque = m_MsgDeque;
			m_MsgDeque.clear();
		}
		for (deque<LOG_MSG>::const_iterator iter = tmpDeque.begin(); iter != tmpDeque.end(); ++iter)
		{
			Log(*iter);
		}
		tmpDeque.clear();

		Sleep(20);
	}

	return 0;
}

void CLogger::init()
{
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	filePath = "LOG_" + m_logName + "/";
	CreateDirectory(filePath.c_str(), NULL);
	
	string logName = filePath + "log_" + string(GetTimeStr2()) + ".log";
	int iRet= fopen_s(&pFile,logName.c_str(), "a+");
	if (iRet != 0)
	{
		pFile = NULL;
		cout << "��ʼ����־�ļ�ʧ��" << endl;
	}

	logTypeString[LOG_LEVEL_INFO] = "Info: ";
	logTypeString[LOG_LEVEL_DEBUG] = "Debug: ";
	logTypeString[LOG_LEVEL_ERROR] = "Error: ";
	logTypeString[LOG_LEVEL_WARNING] = "Waring: ";
	logTypeString[LOG_LEVEL_UNKOWN] = "Unkown: ";
}

void CLogger::Log(LOG_MSG msg)
{
	// �����̨���ļ�д����־�������־�ļ��е����������˶�������ֵ������дһ���ļ�
	string strTime = GetTimeStr();
	
	static int iCount = 0;

	// 1.������д�����̨
	stringstream ss;
	switch (msg._level)
	{
	case LOG_LEVEL_INFO:    // ��ͨ������־
	{
		SetConsoleTextAttribute(stdHandle, INFO_COLOR);
		ss << m_logName << " " << strTime << " " << logTypeString[msg._level] << msg.msgBuff << endl;
	}
	break;
	case LOG_LEVEL_DEBUG:   // ����������־
	{
		SetConsoleTextAttribute(stdHandle, DEBUG_COLOR);
		ss << m_logName << " " << strTime << " " << logTypeString[msg._level] << msg.msgBuff << endl;
	}
	break;
	case LOG_LEVEL_WARNING: // ����������־
	{
		SetConsoleTextAttribute(stdHandle, WARNING_COLOR);
		ss << m_logName << " " << strTime << " " << logTypeString[msg._level] << msg.msgBuff << endl;
	}
	break;
	case LOG_LEVEL_ERROR:   // ����������־
	{
		SetConsoleTextAttribute(stdHandle, ERROR_COLOR);
		ss << m_logName << " " << strTime << " " << logTypeString[msg._level] << msg.msgBuff << endl;
	}
	break;
	case LOG_LEVEL_UNKOWN:
	default:
		SetConsoleTextAttribute(stdHandle, INFO_COLOR);
		ss << "δ֪����־����" << endl;
		break;
	}
	cout << ss.str();
	SetConsoleTextAttribute(stdHandle, NORMAL_COLOR);
	
	// 2.������д���ļ�
	if (pFile) // ����ļ��Ѿ���,��ֱ�����ļ���д������
	{
		if (iCount > MAX_COUNT) 
		{
			fflush(pFile);
			fclose(pFile);
			string logName = filePath + "log_" + GetTimeStr2() + ".log";
			int iRet = fopen_s(&pFile,logName.c_str(), "a+");
			if (iRet != 0)
			{
				cout << "���´��ļ�ʧ��" << endl;
				pFile = NULL;
			}
			iCount = 0;
		}
		if (pFile)
		{
			fprintf(pFile, "%s", ss.str().c_str());
			fflush(pFile);
		}
		++iCount; // �ɹ�д������
	}
}

void CLogger::ConstructMsg(LOG_MSG * msg, const char* format)
{
	if (msg == NULL)
	{
		return;
	}
	va_list args; 
	va_start(args, format); 
	vsprintf_s(msg->msgBuff, format, args); 
	va_end(args); 
}

string GetTimeStr()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	char strTime[20];
	//sprintf(strTime, "%04d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	sprintf_s(strTime,20, "%04d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	return string(strTime);
}

string GetTimeStr2()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	char strTime[20];
	//sprintf(strTime, "%04d-%02d-%02d %02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	sprintf_s(strTime, 20, "%04d-%02d-%02d-%02d-%02d-%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	return string(strTime);
}
