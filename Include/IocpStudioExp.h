/////////////////////////////////////////////////////////////////////////////
// Name:        IocpStudio.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef IocpStudio_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"IocpStudiod.lib")
#else
#pragma comment(lib,"IocpStudio.lib")
#endif

#define IocpStudio_OP_API extern "C" _declspec(dllimport)
#endif

// ��ʼ��IOCP,����HANDLE of IOCP
IocpStudio_OP_API void* Iocp_Init();
// ֹͣ,Ҫ���ͷ���Դǰֹͣ
IocpStudio_OP_API bool Iocp_Stop();