#ifndef ILOCK_H_
#define ILOCK_H_

#include<Windows.h>

/*
多线程互斥锁的接口类
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
多线程：临界区实现类
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
多线程：最终使用的实现类
	1.本类暂时使用临界区作为互斥的变量，以后如果需要扩展成互斥量之类的，只需继承ILock接口，并在此增加对应的构造函数即可
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

