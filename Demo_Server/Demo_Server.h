
// Demo_Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDemo_ServerApp:
// �йش����ʵ�֣������ Demo_Server.cpp
//

class CDemo_ServerApp : public CWinAppEx
{
public:
	CDemo_ServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDemo_ServerApp theApp;