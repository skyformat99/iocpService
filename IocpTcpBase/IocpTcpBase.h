// IocpTcpBase.h : IocpTcpBase DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// IocpTcpBaseApp
// �йش���ʵ�ֵ���Ϣ������� IocpTcpBase.cpp
//

class IocpTcpBaseApp : public CWinApp
{
public:
	IocpTcpBaseApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
