// IocpServer.h : IocpServer DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// IocpServerApp
// �йش���ʵ�ֵ���Ϣ������� IocpServer.cpp
//

class IocpServerApp : public CWinApp
{
public:
	IocpServerApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
