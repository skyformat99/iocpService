/////////////////////////////////////////////////////////////////////////////
// Name:        OverPool.cpp
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#define OverPool_OP_API extern "C" _declspec(dllexport)
#include "OverPoolExp.h"
#include "OverBase.h"
COverBase Ov;
// ��ʼ��
OverPool_OP_API bool Ov_Init(int BufferSize)
{
	return Ov.Init(BufferSize);
}
// ���Ov�ṹ
OverPool_OP_API void* Ov_GetOverlapped()
{
	return Ov.GetOver();
}
// �ͷ�Ov�ṹ
OverPool_OP_API void Ov_ReleaseOverlapped(void* pOverlapped)
{
	Ov.ReleaseOver((OVERLAPPED_PLUS*)pOverlapped);
}