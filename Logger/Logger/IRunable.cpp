#include "IRunable.h"



IRunable::IRunable()
{
	m_handle = nullptr;
}


IRunable::~IRunable()
{
	CloseHandle(m_handle);
}

void IRunable::Start()
{
	m_handle =(HANDLE)_beginthreadex(nullptr,0,ThreadFunc,this, 0, nullptr);
}

void IRunable::End()
{
	TerminateThread(m_handle, 0);
}

HANDLE IRunable::GetHandle()
{
	return m_handle;
}

bool IRunable::IsRunning()
{
	return (m_handle == nullptr);
}

UINT IRunable::ThreadFunc(void * lp)
{
	IRunable *pThread = reinterpret_cast<IRunable*>(lp);
	unsigned int ret = 0;
	if (pThread)
	{
		ret = pThread->Run();
		pThread->m_handle = nullptr;
	}
	return ret;
}
