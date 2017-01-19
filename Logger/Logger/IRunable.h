#ifndef IRUNABLE_H_
#define IRUNABLE_H_

/*
运行时线程的基类，其可派生出不同类型的线程类
*/
#include<Windows.h>
#include<process.h>

class IRunable
{
public:
	IRunable();
	virtual ~IRunable();
public:
	// 纯虚函数，具体的实现由子类去实现
	virtual unsigned int Run() = 0;
	void Start();
	void End();
	HANDLE GetHandle();
	bool IsRunning();
private:
	static UINT __stdcall ThreadFunc(void* lp);
	HANDLE m_handle;
};

#endif // !IRUNABLE_H_
