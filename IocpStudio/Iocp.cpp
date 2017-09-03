#include "StdAfx.h"
#include "Iocp.h"

CIocp::CIocp(void)
:m_hIocp(NULL)
, m_nThreads(0)
,m_pThreads(NULL)
{
}

CIocp::~CIocp(void)
{
	if (m_hIocp)
	{
		CloseHandle(m_hIocp);
	}
	if (m_pThreads)
	{
		delete[] m_pThreads;
	}
}

// ֹͣ��ɶ˿�
bool CIocp::Stop(void)
{
	if (!m_hIocp)
	{
		return true;
	}
	for(int i=0;i<m_nThreads;i++)
	{
		PostQueuedCompletionStatus(m_hIocp, 0, (DWORD)EXIT_CODE, NULL);
		Sleep(1);
	}
	 WaitForMultipleObjects(m_nThreads,m_pThreads, TRUE, INFINITE);
	return true;
}
// ��ʼ����ɶ˿�
void* CIocp::Init()
{
	if (m_hIocp)
	{
		return m_hIocp;
	}
	// ��ʼ��IOCP
	// ������һ����ɶ˿�
	m_hIocp=CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0 );
	if (NULL==m_hIocp)
	{
		/*CFileLog log;
		log	.WriteLog(1,_T("������ɶ˿�ʧ�ܣ��������: %d��"), WSAGetLastError());*/
		return NULL;
	}
	// ���������߳�
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	m_nThreads=si.dwNumberOfProcessors*2+2;
	m_pThreads=new HANDLE[m_nThreads];
	DWORD nThreadID=0;
	for (int i=0;i<m_nThreads;i++)
	{
		m_pThreads[i]=CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WorkerThread,this, 0, &nThreadID);
		// QueueUserWorkItem((LPTHREAD_START_ROUTINE)WorkerThread,this,WT_EXECUTEDEFAULT );
	}
	return m_hIocp;
}

// ��Iocp
bool CIocp::BindIocp(HANDLE hHandle,void* lpCompletionKey)
{
	if(!m_hIocp||NULL== CreateIoCompletionPort(hHandle,m_hIocp,(DWORD)lpCompletionKey, 0))
	{
		/*CFileLog log;
		log.WriteLog(1,"����ɶ˿�ʧ�ܣ��������: %d��", WSAGetLastError());*/
		return false;
	}
	return true;
}
// �����߳�
DWORD /*WINAPI*/ CIocp::WorkerThread(CIocp* lpVoid)
{
	OVERLAPPED* lpOverlapped = NULL;
	COMPLETION_KEY_IOCP* lpCompletionKey = NULL;
	DWORD dwBytesTransfered = 0;
	BOOL bReturn=FALSE;
	while(TRUE)
	{
		bReturn = GetQueuedCompletionStatus(lpVoid->m_hIocp,
			&dwBytesTransfered,(PULONG_PTR)&lpCompletionKey,&lpOverlapped,
			INFINITE);
		// ����յ������˳���־����ֱ���˳�
		if (EXIT_CODE==(DWORD)lpCompletionKey) // �߳��˳�
		{
			break;
		}
		else
		{
			// �ڲ��ص�����
			lpCompletionKey->m_DoOutFun(bReturn,dwBytesTransfered,lpCompletionKey,lpOverlapped,lpCompletionKey->m_pVoid);
		}
	}
	return 0;
}

