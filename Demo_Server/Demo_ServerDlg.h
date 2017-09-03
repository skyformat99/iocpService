
// Demo_ServerDlg.h : ͷ�ļ�
//

#pragma once

#include "BusStruct.h"

// CDemo_ServerDlg �Ի���
class CDemo_ServerDlg : public CDialog
{
// ����
public:
	CDemo_ServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMO_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtCreate();
	HANDLE m_hIocp;
	afx_msg void OnClose();
	static void DoInMonitor(BOOL bRes,unsigned long dwBytesTransfered,SOCKET nSocket,
		char* lpOverlapped,CDemo_ServerDlg* lpVoid);

	static void DoOutFun(BOOL bRes,unsigned long dwBytesTransfered,SERVER_COMPLETIONKEY* lpCompletionKey,
		SERVER_OVER* lpOverlapped,CDemo_ServerDlg* lpVoid);

	afx_msg void OnBnClickedBtTest();
};
