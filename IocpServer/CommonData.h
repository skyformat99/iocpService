#ifndef _COMMON_DATA_IO_
#define _COMMON_DATA_IO_
#include "Common.h"
typedef struct _OVERLAPPED_PLUS:public OVERLAPPEDEX
{
	DWORD			m_BufferSize; // ���ݴ�С
	_OVERLAPPED_PLUS()
	{
		m_BufferSize=0;
	}
}OVERLAPPED_PLUS;
typedef struct _COMPLETION_KEY_NET:public COMPLETION_KEY
{
	DoFun m_DoInFun;  // �ڻص�����(��һ��)
	SOCKET m_Socket;
	// ��������
	unsigned long m_nLeftBytes;
	unsigned long m_nDataLen;
}COMPLETION_KEY_NET;
#endif
