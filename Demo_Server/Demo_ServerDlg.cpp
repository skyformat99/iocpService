
// Demo_ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo_Server.h"
#include "Demo_ServerDlg.h"
#include "IocpServerExp.h"
#include "IocpStudioExp.h"
#include "LinkPool.h"
#include "IocpTcpBaseExp.h"


CLinkPool<SERVER_COMPLETIONKEY> g_KeyPool;
CLinkPool<SERVER_OVER> g_OverPool;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDemo_ServerDlg �Ի���




CDemo_ServerDlg::CDemo_ServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemo_ServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemo_ServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemo_ServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_CREATE, &CDemo_ServerDlg::OnBnClickedBtCreate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BT_TEST, &CDemo_ServerDlg::OnBnClickedBtTest)
END_MESSAGE_MAP()


// CDemo_ServerDlg ��Ϣ�������

BOOL CDemo_ServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼ������
	m_hIocp=Iocp_Init();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDemo_ServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemo_ServerDlg::OnPaint()
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
HCURSOR CDemo_ServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDemo_ServerDlg::OnBnClickedBtCreate()
{
	if(IocpSer_CreateServer(m_hIocp,6688,DoInMonitor,this))
	{
		GetDlgItem(IDC_BT_CREATE)->EnableWindow(FALSE);
	}
}

void CDemo_ServerDlg::OnClose()
{
	Iocp_Stop();
	CDialog::OnClose();
}
int nSock=123;
void CDemo_ServerDlg::DoInMonitor(BOOL bRes,unsigned long dwBytesTransfered,SOCKET nSocket,
				 char* lpOverlapped,CDemo_ServerDlg* lpVoid)
{
	SERVER_COMPLETIONKEY* pKey=g_KeyPool.GetData();
	pKey->m_Socket=nSocket;
	IocpTcp_BindIocp(pKey->m_Socket,lpVoid->m_hIocp,pKey);
	pKey->m_DoOutFun=(DoFun)DoOutFun;
	SERVER_OVER* pOver=g_OverPool.GetData();
	if (!pOver->m_pBuffer)
	{
		pOver->m_pBuffer=new char[81960];
	}
	// ��ʼ��
	pOver->m_nDataLen=0;
	pOver->m_nLeftBytes=4;
	pOver->m_OpType=RECV_POSTED;
	if(!IocpTcp_PostRecv(nSocket,pOver,pOver->m_pBuffer,4))
	{
		g_OverPool.BackData(pOver);
		IocpTcp_StopSock(nSock);
		g_KeyPool.BackData(pKey);
	}

}
void CDemo_ServerDlg::DoOutFun(BOOL bRes,unsigned long dwBytesTransfered,SERVER_COMPLETIONKEY* lpCompletionKey,
			  SERVER_OVER* lpOverlapped,CDemo_ServerDlg* lpVoid)
{
	if (!lpOverlapped)
	{
		return;
	}
	if (!bRes||dwBytesTransfered==0)
	{
		switch (lpOverlapped->m_OpType)
		{
		case RECV_POSTED:
			{
				TRACE("-----Socket:%u�Ͽ�.��Դ����.-----\n",lpCompletionKey->m_Socket);
				IocpTcp_StopSock(lpCompletionKey->m_Socket);
				g_KeyPool.BackData(lpCompletionKey);
			}
		case SEND_POSTED:
			{
				//lpCompletionKey->ReleaseContext(8);
			}
			break;
		default:
			break;
		}
		g_OverPool.BackData(lpOverlapped);
		return;
	}
	switch (lpOverlapped->m_OpType)
	{
	case SEND_POSTED:
		{
			//lpCompletionKey->ReleaseContext(8);
		}
		break;
	case RECV_POSTED:
		{
			if (0==lpOverlapped->m_nDataLen) // ���ճ�������
			{
				lpOverlapped->m_nLeftBytes-=dwBytesTransfered;
				if (lpOverlapped->m_nLeftBytes>0)
				{
					if(!IocpTcp_PostRecv(lpCompletionKey->m_Socket,
						lpOverlapped,lpOverlapped->m_pBuffer+(4-lpOverlapped->m_nLeftBytes),lpOverlapped->m_nLeftBytes))
					{
						IocpTcp_StopSock(lpCompletionKey->m_Socket);
						g_KeyPool.BackData(lpCompletionKey);
						g_OverPool.BackData(lpOverlapped);
					}
				}
				else
				{
					lpOverlapped->m_nLeftBytes=lpOverlapped->m_nDataLen=*(int*)lpOverlapped->m_pBuffer;
					//TRACE("-----�������ݳ���:%u.-----\n",lpOverlapped->m_nDataLen);
					// �������ݲ���
					if(!IocpTcp_PostRecv(lpCompletionKey->m_Socket,lpOverlapped,lpOverlapped->m_pBuffer,lpOverlapped->m_nDataLen))
					{
						IocpTcp_StopSock(lpCompletionKey->m_Socket);
						g_KeyPool.BackData(lpCompletionKey);
						g_OverPool.BackData(lpOverlapped);
					}
				}
			}
			else // �������ݲ���
			{
				lpOverlapped->m_nLeftBytes-=dwBytesTransfered;
				if (lpOverlapped->m_nLeftBytes>0)
				{
					if(!IocpTcp_PostRecv(lpCompletionKey->m_Socket,lpOverlapped,
						lpOverlapped->m_pBuffer+(lpOverlapped->m_nDataLen-lpOverlapped->m_nLeftBytes),lpOverlapped->m_nLeftBytes))
					{
						IocpTcp_StopSock(lpCompletionKey->m_Socket);
						g_KeyPool.BackData(lpCompletionKey);
						g_OverPool.BackData(lpOverlapped);
					}
				}
				else // �������յ�����
				{
					TRACE("-----�����������,ʱ��:%u-----\n",clock());
					// ��������
					g_OverPool.BackData(lpOverlapped);
					SERVER_OVER* pOver=g_OverPool.GetData();
					if (!pOver->m_pBuffer)
					{
						pOver->m_pBuffer=new char[81960];
					}
					// ��ʼ��
					pOver->m_nDataLen=0;
					pOver->m_nLeftBytes=4;
					pOver->m_OpType=RECV_POSTED;
					if(!IocpTcp_PostRecv(lpCompletionKey->m_Socket,pOver,pOver->m_pBuffer,4))
					{
						IocpTcp_StopSock(lpCompletionKey->m_Socket);
						g_KeyPool.BackData(lpCompletionKey);
						g_OverPool.BackData(pOver);
					}
				}
			}
		}
	default:
		break;
	}
}
void CDemo_ServerDlg::OnBnClickedBtTest()
{
	int nRes=closesocket(nSock);
}
