#include "Logger.h"

CLogger::CLogger()
{
	m_bIsRunning = true;
}

CLogger::CLogger(string _name)
	:m_logName(_name)
{
	m_bIsRunning = true;
}

CLogger::~CLogger()
{
}

void CLogger::info(const char * format, ...)
{
	if (!m_bIsRunning) return;

	LOG_MSG msg;
	msg._level = LOG_LEVEL::LOG_LEVEL_INFO;

	GetLogMsg(msg)
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

	GetLogMsg(msg)
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

	GetLogMsg(msg)
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

	GetLogMsg(msg)
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

void CLogger::Log(LOG_MSG msg)
{
}
