
// OverTestDlg.h : ͷ�ļ�
//

#pragma once

// COverTestDlg �Ի���
class COverTestDlg : public CDialog
{
// ����
public:
	COverTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OVERTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtCreate();
	afx_msg void OnBnClickedBtGet();
	afx_msg void OnBnClickedBtRel();
	static DWORD OperTh(COverTestDlg* pVoid);
};
