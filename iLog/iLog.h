// iLog.h : iLog DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// iLogApp
// �йش���ʵ�ֵ���Ϣ������� iLog.cpp
//

class iLogApp : public CWinApp
{
public:
	iLogApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
