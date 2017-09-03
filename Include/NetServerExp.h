/////////////////////////////////////////////////////////////////////////////
// Name:        NetServer.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef NetServer_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"NetServerd.lib")
#else
#pragma comment(lib,"NetServer.lib")
#endif
#define NetServer_OP_API extern "C" _declspec(dllimport)
#endif
// ��ʼ�������� INVALID_SOCKET
NetServer_OP_API bool NetSvr_Init(HANDLE hIocp, unsigned short nPort,
								  void* OutDoFun=NULL,void* pObj=NULL,char* szSerIp=NULL);
// ����˷��� 1,����,0,-1 ����,2����
NetServer_OP_API int NetSvr_PostSend(void* lpCompletionKey,void* pOverlapped,int Cmd,DWORD dwBytesLen);
// �ر�����,bCompleted�����Ƿ�������з���(����Pending),������������
NetServer_OP_API bool NetSvr_Release(void* lpCompletionKey,bool bCompleted=false);

// ֹͣ�����
NetServer_OP_API bool NetSvr_Stop();