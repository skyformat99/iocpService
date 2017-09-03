#pragma once
/*************************˵��*******************************
1.����CPU����ȷ���߳�����(���߳�����)
2.���ûص��ķ�ʽ��չ����ӿ�
3.Key�ṹ�������ֱ�����ͬ,Over�ṹ��Ȼ
*************************˵��*******************************/
// ���ݸ�Worker�̵߳��˳��ź�
#define EXIT_CODE NULL
typedef void (*DoFun)(BOOL bRes,DWORD dwBytesTransfered,
					  void* lpCompletionKey,void* lpOverlapped,void* pVoid);
typedef struct _COMPLETION_KEY_IOCP
{
	// -----�ⲿ�����-----
	DoFun m_DoOutFun; // �ⲿ������
	void* m_pVoid;    // ��ص�����
	void* m_pObj;     // ��������

	_COMPLETION_KEY_IOCP* pLink;
	_COMPLETION_KEY_IOCP* pNext;
}COMPLETION_KEY_IOCP;

class CIocp
{
public:
	CIocp(void);
	~CIocp(void);
private:
	// ��ɶ˿�,ÿ��������ֻ��һ��
	HANDLE m_hIocp;
	// �̸߳���
	int m_nThreads;
	HANDLE* m_pThreads;
private:
	// �����߳�
	static DWORD /*WINAPI*/ WorkerThread(CIocp* lpVoid);
	// ��Iocp
	bool BindIocp(HANDLE hHandle,void* lpCompletionKey);
public:
	// ��ʼ����ɶ˿�,�߳�����,0ΪĬ���߳���
	void* Init();
	// ֹͣ��ɶ˿�
	bool Stop(void);
};
