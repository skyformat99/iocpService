#pragma once

typedef enum _OPERATION_TYPE  
{
	NULL_POSTED,    // ���ڳ�ʼ����������
	ACCEPT_POSTED, // ��־Ͷ�ݵ�Accept����
	SEND_POSTED,   // ��־Ͷ�ݵ��Ƿ��Ͳ���
	RECV_POSTED,   // ��־Ͷ�ݵ��ǽ��ղ���
	WRITE_POSTED,  // ��־Ͷ�ݵ���д�����
	READ_POSTED,   // ��־Ͷ�ݵ��Ƕ�ȡ����

}OPERATION_TYPE;

typedef struct _OVERLAPPED_PLUS
{
	OVERLAPPED      m_Overlapped; // �ص��ṹ
	OPERATION_TYPE  m_OpType;     // ������ʶ
	char*           m_pBuffer;    // ����

	DWORD			m_BufferSize; // ���ݴ�С
	DWORD			m_dwFlags;
	DWORD			m_dwBytes;
	WSABUF			m_wsaBuf[1];
	_OVERLAPPED_PLUS()
	{
		m_OpType=NULL_POSTED;
		ZeroMemory(&m_Overlapped,sizeof(OVERLAPPED));
		m_pBuffer=NULL;
		m_BufferSize=0;
		m_dwFlags=0;
		m_dwBytes=0;
	}
	~_OVERLAPPED_PLUS()
	{
		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
	}
}OVERLAPPED_PLUS;

typedef struct _I_DATA
{
	char* pData;
}I_DATA;

typedef struct _OVER_DATA
{
	I_DATA pData;
	_OVER_DATA* pLink;
	_OVER_DATA* pNext;
}OVER_DATA;

class COverBase
{
public:
	COverBase(void);
	~COverBase(void);
private:
	CRITICAL_SECTION m_cs;
	// ���ݴ�С
	int m_nSize;
	// ��������ͷָ��
	OVER_DATA* m_pIdle;
	// ������ͷ
	OVER_DATA* m_pLink;
public:
	// ��ʼ��
	bool Init(int nSize);
	// ��ȡ��������
	void* GetOver();
	// �ͷ�Over
	void ReleaseOver(OVER_DATA* pOver);
};
