#ifndef LOGGER_H_
#define LOGGER_H_

#include "IRunable.h"
#include "ILock.h"
#include<iostream>
#include<string>
#include<deque>

using namespace std;

#define MAX_BYTE 1024   // 单条日志的最大长度
#define MAX_COUNT 5000  // 单个日志文件存储的最大日志条目数量

#define GetLogMsg(msg) \
	va_list args; \
	va_start(args, format); \
	vsprintf(msg.msgBuff, format, args); \
	va_end(args); \

// 声明一个全局的Log指针
extern CLogger * pLog;
/*
日志类，继承线程类，日志为一个单独的线程,在程序运行中，不占用主线程资源
*/

class CLogger :
	public IRunable
{
public:
	// 日志类相关定义

	/* 日志级别定义
	*/
	enum LOG_LEVEL
	{
		LOG_LEVEL_UNKOWN,  // 未知类型日志
		LOG_LEVEL_INFO,    // 普通类型日志
		LOG_LEVEL_DEBUG,   // 调试类型日志
		LOG_LEVEL_WARNING, // 警告类型日志
		LOG_LEVEL_ERROR,   // 错误类型日志
	};

	/* 单条日志数据结构
	*/
	struct LOG_MSG
	{
		LOG_LEVEL _level;  // 日志的级别
		char msgBuff[MAX_BYTE]; // 日志内容

		LOG_MSG()
		{
			_level = LOG_LEVEL_UNKOWN;
			memset(msgBuff, 0, sizeof(msgBuff));
		}
	};

public:
	/* 对外部的接口
	*/

	/* 获取日志名称
	*/
	string GetName() { return m_logName; }

	/* info类型的日志
	*/
	void info(const char* format, ...);

	/* debug类型的日志
	*/
	void debug(const char* format, ...);

	/* warning类型的日志
	*/
	void warning(const char* format, ...);

	/* error类型的日志
	*/
	void error(const char* format, ...);

public:
	CLogger();
	CLogger(string _name);
	virtual ~CLogger();

	virtual unsigned int Run();
private:

	void Log(LOG_MSG msg);

	bool m_bIsRunning;  // 线程是否运行的标志
	string m_logName;

	CCriticalSection m_cs;      // 互斥变量
	deque<LOG_MSG> m_MsgDeque;  // 日志信息队列
};

#endif // !LOGGER_H_


