// OverPool.h : OverPool DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// OverPoolApp
// �йش���ʵ�ֵ���Ϣ������� OverPool.cpp
//

class OverPoolApp : public CWinApp
{
public:
	OverPoolApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
