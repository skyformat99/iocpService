#include "StdAfx.h"
#include "OverBase.h"

COverBase::COverBase(void)
: m_nSize(0)
,m_pIdle(NULL)
,m_pLink(NULL)
{
	InitializeCriticalSection(&m_cs);
}

COverBase::~COverBase(void)
{
	OVER_DATA* pOv=m_pLink;
	OVER_DATA* pLink=NULL;
	while (pOv)
	{
		TRACE("-------д������:%u------\n",*((int*)pOv->pData.pData));
		delete[] pOv->pData.pData;
		pLink=pOv->pLink;
		delete pOv;
		pOv=pLink;
	}
	DeleteCriticalSection(&m_cs);
}

// ��ʼ��
bool COverBase::Init(int nSize)
{
	m_nSize=nSize;
	m_pIdle=new OVER_DATA();
	m_pIdle->pData.pData=new char[m_nSize];
	m_pIdle->pNext=NULL;
	m_pIdle->pLink=NULL;
	m_pLink=m_pIdle;
	return true;
}

// ��ȡ��������
void* COverBase::GetOver()
{
	OVER_DATA* pOv=NULL;
	EnterCriticalSection(&m_cs);
	if (m_pIdle)
	{
		pOv=m_pIdle;
		m_pIdle=pOv->pNext;
	}
	else
	{
		pOv=new OVER_DATA();
		pOv->pData.pData=new char[m_nSize];
		pOv->pNext=NULL;
		pOv->pLink=m_pLink;
		m_pLink=pOv;
	}
	LeaveCriticalSection(&m_cs);
	return pOv;
}

// �ͷ�Over
void COverBase::ReleaseOver(OVER_DATA* pOv)
{
	EnterCriticalSection(&m_cs);
	pOv->pNext=m_pIdle;
	m_pIdle=pOv;
	LeaveCriticalSection(&m_cs);
}
