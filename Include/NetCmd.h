#ifndef _COMMON_STRUCT_NET_
#define _COMMON_STRUCT_NET_
#include "Common.h"
typedef enum _OP_RESULT
{
	OP_OK,                 // �����ɹ�
	CAM_INIT_ERROR,        // �����ʼ������
	TIMERQUEUE_INIT_ERROR, // �̶߳��г�ʼ��ʧ��
	OPEN_SQL_ERROR,
	EXCUTE_SQL_ERROR,
	CAM_EXIST,
	CAM_NOEXIST,
	TASK_EXIST,
	TASK_NOEXIST,
	TRANS_ADD_ERROR,
	REC_READ_ERROR,
}OP_RESULT;
typedef enum _CONNECT_CMD  //CMD
{
	// �ظ��������
	NET_OP_RESULT,
	// Cam����
	CAM_ADD=1,
	CAM_ADD_REPLY,
	CAM_EDIT,
	CAM_SELECT,
	CAM_SELECT_REPLY,
	CAM_DELETE,
	// �������
	TASK_ADD,
	TASK_START,
	TASK_STOP,
	TASK_SELECT,
	TASK_SELECT_REPLY,
	TASK_DELETE,
	// ��Ƶ���ݲ���
	VIDEO_START,
	VIDEO_DATA,
	// ¼��طŲ���
	REC_PLAY,
	REC_DOWN,
	// RoSeek��������
	CAM_DATA,
}CONNECT_CMD;
#pragma pack (1) /*ָ����1�ֽڶ���*/
// ��ͷ
typedef struct _CMD_HEAD_DATA
{
	long Cmd;
	long Len;
	char Data[1];
}CMD_HEAD_DATA;

// Cam Op
typedef struct _CAM_OP_DATA
{
	long  CamId;
	long  Pid;
	char  CamName[32];
	short CamType;
	char  CamIp[16];
	unsigned short Port;
	char  User[32];
	char  Pass[16];
	long   CamRot;
}CAM_OP_DATA;

// Task OP
typedef struct _TASK_SEL_DATA
{
	long  CamId;
	short Status;
}TASK_SEL_DATA;
// REC Start
typedef struct _VIDEO_START_DATA
{
	long  CamId;
	short CamType;
	char  CamIp[16];
	unsigned short Port;
	char  User[32];
	char  Pass[16];
}VIDEO_START_DATA;

typedef struct _REC_PLAY_DATA
{
	long  CamId;
	LONGLONG sTime;
	LONGLONG eTime;
}REC_PLAY_DATA;
typedef union _LARGE_DATA
{
	struct {
		LONG Cmd;
		LONG nType;// 0ͷ����,1 ֡����
	};
	LONGLONG Time; // ʱ��
	struct {
		DWORD LowPart;
		LONG HighPart;
	};
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
	LONGLONG QuadPart;
}LARGE_DATA;

typedef struct _INDEX_DATA // ������Ϣ
{
	LARGE_DATA offPos;  // λ��ƫ��
	LARGE_DATA eTime;   // ����ʱ��
	short      tLong;   // ����ʱ��
	LONG       dLong;   // ���ݳ���
}INDEX_DATA;

#pragma pack () /*ȡ��ָ�����룬�ָ�ȱʡ����*/
#endif