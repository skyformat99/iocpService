
// OverTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OverTest.h"
#include "OverTestDlg.h"
#include "OverPoolExp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COverTestDlg �Ի���




COverTestDlg::COverTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COverTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COverTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COverTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_CREATE, &COverTestDlg::OnBnClickedBtCreate)
	ON_BN_CLICKED(IDC_BT_GET, &COverTestDlg::OnBnClickedBtGet)
	ON_BN_CLICKED(IDC_BT_REL, &COverTestDlg::OnBnClickedBtRel)
END_MESSAGE_MAP()


// COverTestDlg ��Ϣ�������

BOOL COverTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Ov_Init(8192);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COverTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COverTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COverTestDlg::OnBnClickedBtCreate()
{
	TRACE("-----��ʱ:%u-----\n",clock());
	for (int i=0;i<6;i++)
	{
		DWORD dw;
		HANDLE handle=CreateThread(NULL,0,LPTHREAD_START_ROUTINE(OperTh),this,0,&dw);
		if (NULL!=handle)
		{
			CloseHandle(handle);
		}
		Sleep(1);
	}
}
void COverTestDlg::OnBnClickedBtGet()
{
}

void COverTestDlg::OnBnClickedBtRel()
{
}

DWORD COverTestDlg::OperTh(COverTestDlg* pVoid)
{
	static int Num=0;
	int abc=Num;
	Num+=1000;
	int bcd=Num;
	OVERLAPPEDEX* pNum=NULL;
	char data[8192];
	TRACE("-----1,�߳�:%d��ʱ:%d-----\n",abc,clock());
	for (int i=0;i<100000;i++)
	{
		pNum=(OVERLAPPEDEX*)Ov_GetOverlapped();
		bcd+=i;
		memcpy(data,&bcd,4);
		memcpy(pNum->m_pBuffer,data,8192);
		Ov_ReleaseOverlapped(pNum);
	}
	TRACE("-----2,�߳�:%d��ʱ:%d-----\n",abc,clock());
	return 0;
}
