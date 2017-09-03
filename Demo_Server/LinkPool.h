/***********************˵��***********************
�ɸ��õ�����ṹ.��ȡ,�黹,�ֹ�������,�Ϳ�������,����
��������.
֧�ֶ��̻߳�ȡ,�黹.
�ر��,�黹ʱ,ʹ����Ҫ��ֹͬһԪ�ع黹���λ���.
***********************˵��***********************/
#pragma once

// �ṹ����
#define  LINK_DATA char

typedef struct LINK_STRU
{
	LINK_DATA  Data;
	LINK_STRU* pLink;
	LINK_STRU* pNext;
};
template<class T>
class CLinkPool
{
public:
	CLinkPool(void)
	:m_pLink(NULL)
	,m_pIdle(NULL)
	{
		InitializeCriticalSection(&m_cs);
	}
	~CLinkPool(void)
	{
		int i=0;
		T* pData=m_pLink;
		T* pLink=NULL;
		while (pData)
		{
			pLink=(T*)pData->pLink;
			delete pData;
			pData=pLink;
			i++;
		}
		TRACE("-----Link:%d-----\n",i);
		DeleteCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION m_cs;
	// ���ݴ�С
	int m_nSize;
	// ��������ͷָ��
	T* m_pIdle;
	// ������ͷ
	T* m_pLink;
public:
public:
	// ���һ��Key
	T* GetData(void)
	{
		T* pData=NULL;
		EnterCriticalSection(&m_cs);
		if (m_pIdle) // ��������Ϊ��
		{
			pData=m_pIdle;
			m_pIdle=(T*)pData->pNext;
		}
		else
		{
			pData=new T();
			pData->pNext=NULL;
			pData->pLink=m_pLink; // �����������
			m_pLink=pData;
		}
		LeaveCriticalSection(&m_cs);
		return pData;
	}
	// �黹Data,�������������
	void BackData(T* pData)
	{
		EnterCriticalSection(&m_cs);
		pData->pNext=m_pIdle;
		m_pIdle=pData;
		LeaveCriticalSection(&m_cs);
	}
};
