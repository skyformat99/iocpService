/////////////////////////////////////////////////////////////////////////////
// Name:        RSNetSDK.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef RSNetSDK_OP_API
#else
#pragma comment(lib,"RSNetSDK.lib")
#define RSNetSDK_OP_API extern "C" _declspec(dllimport)
#endif

// ��ʼ��
RSNetSDK_OP_API bool RS_NET_Init(void* hIocp,DWORD BufferSize);
// ʵʱ��Ƶ
RSNetSDK_OP_API void* RS_NET_RealPlay(char* szSerIp,unsigned short nSerPort,void* DataBackFun,void* lpVoid);
// �ͷ�
RSNetSDK_OP_API bool RS_NET_Release(void* lpCpKey);
// ֹͣ
RSNetSDK_OP_API bool RS_NET_Stop();