#ifndef LOGGER_H_
#define LOGGER_H_

#include "IRunable.h"
#include "ILock.h"
#include<iostream>
#include<string>
#include<deque>

using namespace std;

#define MAX_BYTE 1024   // ������־����󳤶�
#define MAX_COUNT 5000  // ������־�ļ��洢�������־��Ŀ����

#define GetLogMsg(msg) \
	va_list args; \
	va_start(args, format); \
	vsprintf(msg.msgBuff, format, args); \
	va_end(args); \

// ����һ��ȫ�ֵ�Logָ��
extern CLogger * pLog;
/*
��־�࣬�̳��߳��࣬��־Ϊһ���������߳�,�ڳ��������У���ռ�����߳���Դ
*/

class CLogger :
	public IRunable
{
public:
	// ��־����ض���

	/* ��־������
	*/
	enum LOG_LEVEL
	{
		LOG_LEVEL_UNKOWN,  // δ֪������־
		LOG_LEVEL_INFO,    // ��ͨ������־
		LOG_LEVEL_DEBUG,   // ����������־
		LOG_LEVEL_WARNING, // ����������־
		LOG_LEVEL_ERROR,   // ����������־
	};

	/* ������־���ݽṹ
	*/
	struct LOG_MSG
	{
		LOG_LEVEL _level;  // ��־�ļ���
		char msgBuff[MAX_BYTE]; // ��־����

		LOG_MSG()
		{
			_level = LOG_LEVEL_UNKOWN;
			memset(msgBuff, 0, sizeof(msgBuff));
		}
	};

public:
	/* ���ⲿ�Ľӿ�
	*/

	/* ��ȡ��־����
	*/
	string GetName() { return m_logName; }

	/* info���͵���־
	*/
	void info(const char* format, ...);

	/* debug���͵���־
	*/
	void debug(const char* format, ...);

	/* warning���͵���־
	*/
	void warning(const char* format, ...);

	/* error���͵���־
	*/
	void error(const char* format, ...);

public:
	CLogger();
	CLogger(string _name);
	virtual ~CLogger();

	virtual unsigned int Run();
private:

	void Log(LOG_MSG msg);

	bool m_bIsRunning;  // �߳��Ƿ����еı�־
	string m_logName;

	CCriticalSection m_cs;      // �������
	deque<LOG_MSG> m_MsgDeque;  // ��־��Ϣ����
};

#endif // !LOGGER_H_


