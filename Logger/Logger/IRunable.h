#ifndef IRUNABLE_H_
#define IRUNABLE_H_

/*
����ʱ�̵߳Ļ��࣬�����������ͬ���͵��߳���
*/
#include<Windows.h>
#include<process.h>

class IRunable
{
public:
	IRunable();
	virtual ~IRunable();
public:
	// ���麯���������ʵ��������ȥʵ��
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
