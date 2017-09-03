#ifndef _COMMON_STRUCT_IO_
#define _COMMON_STRUCT_IO_

typedef enum _OPERATION_TYPE  
{
	NULL_POSTED,    // ���ڳ�ʼ����������
	ACCEPT_POSTED, // ��־Ͷ�ݵ�Accept����
	SEND_POSTED,   // ��־Ͷ�ݵ��Ƿ��Ͳ���
	RECV_POSTED,   // ��־Ͷ�ݵ��ǽ��ղ���
	WRITE_POSTED,  // ��־Ͷ�ݵ���д�����
	READ_POSTED,   // ��־Ͷ�ݵ��Ƕ�ȡ����

}OPERATION_TYPE;
typedef void (*DoFun)(BOOL bRes,DWORD dwBytesTransfered,
					  void* lpCompletionKey,void* lpOverlapped,void* pVoid);
typedef struct _OVERLAPPEDEX
{
	OVERLAPPED      m_Overlapped; // �ص��ṹ
	OPERATION_TYPE  m_OpType;     // ������ʶ
	char*           m_pBuffer;    // ����
	// ---------����������-----------
	_OVERLAPPEDEX* pLink;
	_OVERLAPPEDEX* pNext;
}OVERLAPPEDEX;
typedef struct _COMPLETION_KEY
{
	// -----�ⲿ�����-----
	DoFun m_DoOutFun; // �ⲿ������
	void* m_pVoid;    // ��ص�����
	void* m_pObj;     // ��������
	// ---------����������-----------
	_COMPLETION_KEY* pLink;
	_COMPLETION_KEY* pNext;
}COMPLETION_KEY;
#endif