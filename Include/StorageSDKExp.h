/////////////////////////////////////////////////////////////////////////////
// Name:        StorageSDK.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef StorageSDK_OP_API
#else
#ifdef _DEBUG
#pragma comment(lib,"StorageSDKd.lib")
#else
#pragma comment(lib,"StorageSDK.lib")
#endif
#define StorageSDK_OP_API extern "C" _declspec(dllimport)
#endif
// ��ʼ��
StorageSDK_OP_API bool ST_SDK_Init(void* pWnd,unsigned int LogMsg);
// ��ѯCamera
StorageSDK_OP_API int ST_SDK_SelectCam(void);
StorageSDK_OP_API bool ST_SDK_GetCamData(int nSock,int* CamId,int* Pid,char* CamName,short* CamType,
				char* CamIp,unsigned short* Port,char* User,char* Pass,int* Rot);
StorageSDK_OP_API bool ST_SDK_AddCam(int Pid,char* CamName,short CamType,char* CamIp,unsigned short nPort,char* User,char* Pass,int Rot);
// �༭Camera
StorageSDK_OP_API bool ST_SDK_EditCam(int CamId,char* CamName,short CamType,char* CamIp,unsigned short nPort,char* User,char* Pass,int Rot);
// ɾ��Cam
StorageSDK_OP_API bool ST_SDK_DelCam(int CamId);
// ��ѯ����
StorageSDK_OP_API int ST_SDK_GetTaskStatus(int CamId);
// ��ʼ����
StorageSDK_OP_API bool ST_SDK_StartTask(int CamId);
// ֹͣ����
StorageSDK_OP_API bool ST_SDK_StopTask(int CamId);
// ����¼��
StorageSDK_OP_API void* ST_SDK_PlayRec(void* pWnd,int CamId, short CamType, LONGLONG sTime, LONGLONG eTime);
// ����¼��
StorageSDK_OP_API void* ST_SDK_DownLoadRec(void* pWnd,int CamId, LONGLONG sTime, LONGLONG eTime);
// ʵʱ��ƵԤ��
StorageSDK_OP_API void* ST_SDK_PlayRealVideo(void* pWnd,int CamId, short CamType,
											 char* CamIp,unsigned short Port,char* User,char* Pass);
// ������Ļ
StorageSDK_OP_API void ST_SDK_ResetScreen(void* pDecode);
// ֹͣ����
StorageSDK_OP_API void ST_SDK_StopPlay(void* pDecode);