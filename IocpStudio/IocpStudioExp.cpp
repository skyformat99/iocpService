/////////////////////////////////////////////////////////////////////////////
// Name:        IocpStudio.cpp
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#define IocpStudio_OP_API extern "C" _declspec(dllexport)
#include "IocpStudioExp.h"
#include "Iocp.h"
CIocp Iocp;
// ��ʼ��IOCP,����HANDLE of IOCP
IocpStudio_OP_API void* Iocp_Init()
{
	return Iocp.Init();
}
// ֹͣ,Ҫ���ͷ���Դǰֹͣ
IocpStudio_OP_API bool Iocp_Stop()
{
	return Iocp.Stop();
}