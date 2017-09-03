/////////////////////////////////////////////////////////////////////////////
// Name:        VideoStFiles.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef VideoStFiles_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"VideoStFilesd.lib")
#else
#pragma comment(lib,"VideoStFiles.lib")
#endif

#define VideoStFiles_OP_API extern "C" _declspec(dllimport)
#endif
// -----------------��ʼ��ģ��------------------------------

// ��ʼ��ģ��,��ɶ˿ھ��,�洢·��,Buff��С,��������
VideoStFiles_OP_API bool VstFile_Init(void* hIocp,int StorDay=30);

// ----------------д����------------------------------------

// ���ɴ洢�ļ�
VideoStFiles_OP_API bool VstFile_CreateStorage(int CamId, int nIdx, int nDat);

// ��ʼ��д,����lpCompletionKey,hFile
VideoStFiles_OP_API void* VstFile_InitWrite(int CamId,void* DoOutFun=NULL,void* pVoid=NULL,bool bCompose=false);

// д����
VideoStFiles_OP_API bool VstFile_WriteData(void* lpCompletionKey,void*lpOverlapped);

// дͷ�ļ�
VideoStFiles_OP_API bool VstFile_WriteHead(void* lpCompletionKey,char* pBuffer, int dwBytesLen);

// ���CamId
VideoStFiles_OP_API int VstFile_GetIoCamId(void* lpCompletionKey);

// ------------------��ȡ����---------------------------------

// ��ʼ����,����lpCompletionKey,hFile
VideoStFiles_OP_API void* VstFile_InitRead(int CamId,LONGLONG sTime,LONGLONG eTime,
										   void* DoOutFun=NULL,void* pVoid=NULL);

// ������
VideoStFiles_OP_API bool VstFile_ReadData(void* lpCompletionKey,void*lpOverlapped);

// ��ͷ
VideoStFiles_OP_API bool VstFile_ReadHead(char* pBuffer, int* dwBytesLen, int CamId);

VideoStFiles_OP_API int  VstFile_GetCamId(void* lpCompletionKey);

// ------------------�ͷ���Դ--------------------------------


// �ͷ���Դ
VideoStFiles_OP_API bool VstFile_Release(void* lpCompletionKey);

// ͣ��ģ��,�ͷ���Դ
VideoStFiles_OP_API bool VstFile_Stop();