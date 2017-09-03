/////////////////////////////////////////////////////////////////////////////
// Name:        IocpTcpBase.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef IocpTcpBase_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"IocpTcpBased.lib")
#else
#pragma comment(lib,"IocpTcpBase.lib")
#endif
#define IocpTcpBase_OP_API extern "C" _declspec(dllimport)
#endif
// ��IOCP
IocpTcpBase_OP_API bool IocpTcp_BindIocp(unsigned int nSocket,void* hIocp,void* lpCompletionKey);
// Ͷ�ݽ���
IocpTcpBase_OP_API bool IocpTcp_PostRecv(unsigned int nSocket,void* lpOverlapped,char* pBuffer,DWORD dwBytesLen);
// Ͷ�ݷ���
IocpTcpBase_OP_API bool IocpTcp_PostSend(unsigned int nSocket,void* lpOverlapped,char* pBuffer,DWORD dwBytesLen);
// ֹͣ
IocpTcpBase_OP_API bool IocpTcp_StopSock(unsigned int nSocket,bool bCompleted=false);