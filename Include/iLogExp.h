/////////////////////////////////////////////////////////////////////////////
// Name:        iLog.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef iLog_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"iLogd.lib")
#else
#pragma comment(lib,"iLog.lib")
#endif
#define iLog_OP_API extern "C" _declspec(dllimport)
#endif

// ����Logд��ȼ�
iLog_OP_API int Log_SetLogLevel(int nLevel);
// д��Log
iLog_OP_API void Log_WriteLog(int nLevel,char* Fmt,...);