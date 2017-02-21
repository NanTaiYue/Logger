#ifndef LOGGER_H_
#define LOGGER_H_

#include "IRunable.h"
#include "ILock.h"
#include<iostream>
#include<string>
#include<deque>
#include<map>
#include<sstream>

using namespace std;

#define MAX_BYTE 1024   // ������־����󳤶�
#define MAX_COUNT 5000  // ������־�ļ��洢�������־��Ŀ����

// ������ص���ɫ
#define NORMAL_COLOR (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)  // ������ɫ
#define ERROR_COLOR  (FOREGROUND_RED)										//������ɫ
#define INFO_COLOR	 (NORMAL_COLOR)											//��Ϣ��ɫ
#define WARNING_COLOR (FOREGROUND_GREEN | FOREGROUND_RED)					//������ɫ
#define DEBUG_COLOR	 (FOREGROUND_BLUE)										//������Ϣ��ɫ

class CLogger;

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

	map<LOG_LEVEL, string> logTypeString;

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
	void init();
	void Log(LOG_MSG msg);
	void ConstructMsg(LOG_MSG *msg, const char* format);

	bool m_bIsRunning;  // �߳��Ƿ����еı�־
	string m_logName;
	HANDLE stdHandle;  // ����̨���ھ��
	FILE *pFile;
	string filePath;  // �ļ�Ŀ¼

	CCriticalSection m_cs;      // �������
	deque<LOG_MSG> m_MsgDeque;  // ��־��Ϣ����
};


// ���ߺ��������ص�ǰϵͳʱ����ַ�����ʽ����"2017-02-21 19:19:50"
string GetTimeStr();
string GetTimeStr2();  // ���ظ�ʽ����2017-02-21-19-19-50��

#endif // !LOGGER_H_


