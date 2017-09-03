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

	_OVERLAPPED_PLUS* pLink;
	_OVERLAPPED_PLUS* pNext;
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
	OVERLAPPED_PLUS* m_pIdle;
	// ������ͷ
	OVERLAPPED_PLUS* m_pLink;
public:
	// ��ʼ��
	bool Init(int nSize);
	// ��ȡ��������
	void* GetOver();
	// �ͷ�Over
	void ReleaseOver(OVERLAPPED_PLUS* pOver);
};
