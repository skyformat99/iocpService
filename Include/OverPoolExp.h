/////////////////////////////////////////////////////////////////////////////
// Name:        OverPool.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef OverPool_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"OverPoold.lib")
#else
#pragma comment(lib,"OverPool.lib")
#endif
#define OverPool_OP_API extern "C" _declspec(dllimport)
#endif
//typedef struct OVERLAPPEDEX
//{
//	OVERLAPPED      m_Overlapped; // �ص��ṹ
//	int  m_OpType;     // ������ʶ
//	char*           m_pBuffer;    // ����
//};
// ��ʼ��
OverPool_OP_API bool Ov_Init(int BufferSize=102400);
// ���Ov�ṹ
OverPool_OP_API void* Ov_GetOverlapped();
// �ͷ�Ov�ṹ
OverPool_OP_API void Ov_ReleaseOverlapped(void* pOverlapped);