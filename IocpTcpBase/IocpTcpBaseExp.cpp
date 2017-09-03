/////////////////////////////////////////////////////////////////////////////
// Name:        IocpTcpBase.cpp
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#define IocpTcpBase_OP_API extern "C" _declspec(dllexport)
#include "IocpTcpBaseExp.h"
// ��IOCP
IocpTcpBase_OP_API bool IocpTcp_BindIocp(unsigned int nSocket,void* hIocp,void* lpCompletionKey)
{
	if (NULL==CreateIoCompletionPort((HANDLE)nSocket,
		hIocp, (DWORD)lpCompletionKey, 0))
	{
		TRACE("-----�ͻ�SOCKET��IOCP���ִ���.�������:%d-----",GetLastError());
		return false;
	}
	return true;
}
// Ͷ�ݽ���
IocpTcpBase_OP_API bool IocpTcp_PostRecv(unsigned int nSocket,void* lpOverlapped,char* pBuffer,DWORD dwBytesLen)
{
	ASSERT(INVALID_SOCKET!=nSocket);
	DWORD dwFlags=0,dwBytes=0;
	WSABUF wsaBuf[1];
	wsaBuf[0].len=dwBytesLen;
	wsaBuf[0].buf=pBuffer;
	// ��ʼ��
	((OVERLAPPED*)lpOverlapped)->hEvent=NULL;
	// Ͷ��WSARecv����
	//ZeroMemory(lpOverlapped->m_Overlapped,sizeof(OVERLAPPED));
	if (SOCKET_ERROR==WSARecv((SOCKET)nSocket, wsaBuf, 1,&dwBytes,&dwFlags, (OVERLAPPED*)lpOverlapped, NULL ))
	{
		if(WSA_IO_PENDING!=WSAGetLastError())  
		{
			TRACE("---����˽��մ���SOCKET:%d,�ͷ���Դ,�������:%d---\n",nSocket,WSAGetLastError());
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}
// Ͷ�ݷ���
IocpTcpBase_OP_API bool IocpTcp_PostSend(unsigned int nSocket,void* lpOverlapped,char* pBuffer,DWORD dwBytesLen)
{
	DWORD dwFlags=0,dwBytes=0;
	WSABUF wsaBuf[1];
	wsaBuf[0].len=dwBytesLen;
	wsaBuf[0].buf=pBuffer;
	// ��ʼ��
	((OVERLAPPED*)lpOverlapped)->hEvent=NULL;
	// Ͷ�ݷ���
	//ZeroMemory(&lpOverlapped->m_Overlapped,sizeof(OVERLAPPED));
	if (SOCKET_ERROR==WSASend((SOCKET)nSocket,wsaBuf, 1,&dwBytes,dwFlags,(OVERLAPPED*)lpOverlapped, NULL))
	{
		if(WSA_IO_PENDING!=WSAGetLastError())  
		{
			TRACE("---_COMPLETION_KEY_NET::PostSend ����˷���ʧ��SOCKET:%d,�ͷ���Դ,�������:%d!---\n",nSocket,WSAGetLastError());
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}
// ֹͣ
IocpTcpBase_OP_API bool IocpTcp_StopSock(unsigned int nSocket,bool bCompleted)
{
	LINGER lingerStruct;
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = bCompleted?10:0;
	setsockopt((SOCKET)nSocket, SOL_SOCKET, SO_LINGER,
		(char *)&lingerStruct, sizeof(lingerStruct) );
	//CancelIo((HANDLE)nSocket);
	return 0==closesocket((SOCKET)nSocket);
}