/////////////////////////////////////////////////////////////////////////////
// Name:        NetClient.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef NetClient_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"NetClientd.lib")
#else
#pragma comment(lib,"NetClient.lib")
#endif
#define NetClient_OP_API extern "C" _declspec(dllimport)
#endif

// ��ʼ���ͻ��˷���lpCompletionKey
NetClient_OP_API void* NetCli_Init(void* hIocp,char* szSerIp, unsigned short nSerPort,int nMaxPending,  
								   void* DoOutFun=NULL,void* pVoid=NULL);
// ������Ϣ ����ֵ:0 ��ȷ,-1,����,1����,2����
NetClient_OP_API int NetCli_PostSend(void* lpCompletionKey,void* pOverlapped,int Cmd,DWORD dwBytesLen);
// �ر�����,�Ƿ�ȴ��������(����������)
NetClient_OP_API bool NetCli_Release(void* lpCompletionKey,bool bCompleted=false);
// ֹͣ�ͻ���
NetClient_OP_API bool NetCli_Stop();