// IocpStudio.h : IocpStudio DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// IocpStudioApp
// �йش���ʵ�ֵ���Ϣ������� IocpStudio.cpp
//

class IocpStudioApp : public CWinApp
{
public:
	IocpStudioApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
