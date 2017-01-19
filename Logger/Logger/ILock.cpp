#include "ILock.h"



ILock::ILock()
{
}


ILock::~ILock()
{
}

CCriticalSection::CCriticalSection()
{
	InitializeCriticalSection(&m_cs);
}

CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&m_cs);
}

void CCriticalSection::Lock()
{
	EnterCriticalSection(&m_cs);
}

void CCriticalSection::UnLock()
{
	LeaveCriticalSection(&m_cs);
}

CGuard::CGuard(ILock * pLock)
{
	m_pLock = nullptr;
	m_pLock = pLock;
	if (m_pLock)
	{
		m_pLock->Lock();
	}
}

CGuard::~CGuard()
{
	if (m_pLock)
	{
		m_pLock->UnLock();
		m_pLock = nullptr;
	}
}
