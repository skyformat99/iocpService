/**********************˵��*************************
ҵ�����ݽṹ
***********************˵��*************************/
#pragma once
#include "Common.h"
typedef struct _PKG_HEAD_DATA
{
	int Cmd; // ����
	int Len; // ���ݳ���
}PKG_HEAD_DATA;

typedef struct SERVER_COMPLETIONKEY:public COMPLETION_KEY
{
	// SOCKET
	SOCKET m_Socket;
};
typedef struct SERVER_OVER :public OVERLAPPEDEX
{
	// ��������
	unsigned long m_nLeftBytes;
	unsigned long m_nDataLen;
	SERVER_OVER()
	{
		m_OpType=NULL_POSTED;
		ZeroMemory(&m_Overlapped,sizeof(OVERLAPPED));
		m_pBuffer=NULL;
	}
	~SERVER_OVER()
	{
		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
	}
};