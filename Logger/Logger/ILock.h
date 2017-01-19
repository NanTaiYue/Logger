#ifndef ILOCK_H_
#define ILOCK_H_

#include<Windows.h>

/*
���̻߳������Ľӿ���
*/
class ILock
{
public:
	ILock();
	virtual ~ILock();
public:
	virtual void Lock() = 0;
	virtual void UnLock() = 0;
};

/*
���̣߳��ٽ���ʵ����
*/
class CCriticalSection : public ILock
{
public:
	CCriticalSection();
	virtual ~CCriticalSection();
public:
	void Lock();
	void UnLock();
private:
	CRITICAL_SECTION m_cs; 
};


/*
���̣߳�����ʹ�õ�ʵ����
	1.������ʱʹ���ٽ�����Ϊ����ı������Ժ������Ҫ��չ�ɻ�����֮��ģ�ֻ��̳�ILock�ӿڣ����ڴ����Ӷ�Ӧ�Ĺ��캯������
*/
class CGuard
{
private:
	ILock* m_pLock;
public:
	CGuard(ILock* pLock);
	virtual ~CGuard();
};

#endif // !ILOCK_H_

