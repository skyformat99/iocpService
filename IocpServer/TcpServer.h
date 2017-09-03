/****************************˵��****************************
�����������,���ʵ�ʵ�Key�ṹ
****************************˵��****************************/
#pragma once
#include "CommonData.h"
#include <winsock2.h>
#include <MSWSock.h>
#pragma comment(lib,"ws2_32.lib")

class CTcpServer:public COMPLETION_KEY
{
public:
	CTcpServer(void)
		:m_Socket(INVALID_SOCKET)
		,m_OverAccept(NULL)
	{
		m_DoOutFun=(DoFun)DoInMonitor;
		WSADATA wsaData;
		// ����(һ�㶼�����ܳ���)
		if (NO_ERROR!=WSAStartup(MAKEWORD(2,2), &wsaData))
		{
			TRACE("---��ʼ��WinSock 2.2ʧ��!---\n");
		}
	}
	~CTcpServer(void)
	{
		if (INVALID_SOCKET!=m_Socket)
		{
			closesocket(m_Socket);
			m_Socket=INVALID_SOCKET;
		}
		if (m_OverAccept)
		{
			delete[] m_OverAccept;
		}
		WSACleanup();
	}
private:
	// Accept�ṹ
	typedef struct _OVERLAPPED_ACCEPT
	{
		OVERLAPPED   m_Overlapped; // �ص��ṹ m_Overlapped;
		SOCKET m_Socket;
		char m_Buff[(sizeof(SOCKADDR_IN)+16)*2];
		_OVERLAPPED_ACCEPT()
		{
			ZeroMemory(&m_Overlapped,sizeof(OVERLAPPED));
			m_Socket=INVALID_SOCKET;
		}
		~_OVERLAPPED_ACCEPT()
		{
			if (INVALID_SOCKET!=m_Socket)
			{
				LINGER lingerStruct;
				lingerStruct.l_onoff = 1;
				lingerStruct.l_linger = 0;
				setsockopt(m_Socket, SOL_SOCKET, SO_LINGER,
					(char *)&lingerStruct, sizeof(lingerStruct) );
				CancelIo((HANDLE)m_Socket);
				closesocket(m_Socket);
				m_Socket=INVALID_SOCKET;
			}
		}
	}OVERLAPPED_ACCEPT;

	bool PostAccept(OVERLAPPED_ACCEPT* lpOverlapped)
	{
		ASSERT( INVALID_SOCKET!=m_Socket );
		// ׼������
		DWORD dwBytes = 0;  
		// Ϊ�Ժ�������Ŀͻ�����׼����Socket( ������봫ͳaccept�������� ) 
		lpOverlapped->m_Socket= WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
		if(INVALID_SOCKET==lpOverlapped->m_Socket) 
		{  
			TRACE("-----��������Accept��Socketʧ�ܣ��������: %d-----\n", WSAGetLastError()); 
			return false;  
		} 
		// Ͷ��AcceptEx
		ZeroMemory(&lpOverlapped->m_Overlapped,sizeof(lpOverlapped->m_Overlapped));
		if(!m_lpfnAcceptEx(m_Socket, lpOverlapped->m_Socket,
			&lpOverlapped->m_Buff, 0/*p_wbuf->len - ((sizeof(SOCKADDR_IN)+16)*2*/,
			sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwBytes,& lpOverlapped->m_Overlapped))
		{  
			if(WSA_IO_PENDING!=WSAGetLastError())  
			{  
				TRACE("-----Ͷ�� AcceptEx ����ʧ�ܣ��������: %d-----\n", WSAGetLastError());
				return false;  
			}  
		} 
		return true;
	}
	// �ڲ�����
private:
	DoFun m_DoFun;  // �ڻص�����
	// �����߳�
	SOCKET m_Socket;
	// IOCP���
	HANDLE m_hIocp;
	LPFN_ACCEPTEX m_lpfnAcceptEx;
	//#ifdef _DEBUG
	LPFN_GETACCEPTEXSOCKADDRS m_lpfnGetAcceptExSockAddrs;
	OVERLAPPED_ACCEPT* m_OverAccept;

private:
	// ���ӻص�
	static void DoInMonitor(BOOL bRes,unsigned long dwBytesTransfered,CTcpServer* lpCompletionKey,
		OVERLAPPED_ACCEPT* lpOverlapped,void* lpVoid)
	{
		if (!bRes)
		{
			TRACE(_T("-----�������뷢�����������˳�!-----\n"));
			return;
		}
		char szIp[32];
		//#ifdef _DEBUG
			//OVERLAPPED_ACCEPT* pAccept=CONTAINING_RECORD(lpOverlapped,OVERLAPPED_ACCEPT,m_Overlapped);
		SOCKADDR_IN* ClientAddr = NULL;
		SOCKADDR_IN* LocalAddr = NULL;  
		int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);  
		lpCompletionKey->m_lpfnGetAcceptExSockAddrs(lpOverlapped->m_Buff, 0,  
			sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (LPSOCKADDR*)&LocalAddr, &localLen, (LPSOCKADDR*)&ClientAddr, &remoteLen);
		TRACE(_T("-----�ͻ��� %s:%d ����,ʱ��:%u.-----\n"), inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port),clock());
		sprintf_s(szIp,32,"IP:%s,Port:%d",inet_ntoa(ClientAddr->sin_addr),ntohs(ClientAddr->sin_port));
		//#endif
		SOCKET nSocket=lpOverlapped->m_Socket;
		// ����Ͷ��AcceptEx���ܿͻ�������
		lpCompletionKey->PostAccept(lpOverlapped);
		// ���ӻص�
		lpCompletionKey->m_DoFun(bRes,dwBytesTransfered,(void*)nSocket,szIp,lpVoid);
	}
public:
	// ���ɷ����
	bool CreateServer(HANDLE hIocp, unsigned short nPort,
		void* OutDoMonitor,void* pVoid=NULL,char* szSerIp=NULL)
	{
		m_hIocp=hIocp;
		m_DoFun=(DoFun)OutDoMonitor;// ��������
		m_pVoid=pVoid;
		// ��������Socket
		m_Socket= WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET==m_Socket) 
		{
			TRACE(_T("��ʼ������Socketʧ�ܣ��������: %d."), WSAGetLastError());
			return false;
		}
		// ��������ַ��Ϣ�����ڰ�Socket
		struct sockaddr_in ServerAddress;
		// ����ַ��Ϣ
		ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));
		ServerAddress.sin_family = AF_INET;
		// ������԰��κο��õ�IP��ַ�����߰�һ��ָ����IP��ַ
		if (szSerIp)
		{
			ServerAddress.sin_addr.s_addr = inet_addr(szSerIp);  
		}
		else
		{
			ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		}
		ServerAddress.sin_port = htons(nPort);
		// �󶨵�ַ�Ͷ˿�
		if (SOCKET_ERROR == bind(m_Socket, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress))) 
		{
			TRACE("bind()����ִ�д���");
			return false;
		}
		// ��ʼ���м���
		if (SOCKET_ERROR==listen(m_Socket,SOMAXCONN))
		{
			TRACE("����ʧ�ܣ��������: %d.", WSAGetLastError());
			return false;
		}

		// AcceptEx �� GetAcceptExSockaddrs ��GUID�����ڵ�������ָ��
		GUID GuidAcceptEx = WSAID_ACCEPTEX;  
		GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
		// ��ȡAcceptEx����ָ��
		DWORD dwBytes = 0;  
		if(SOCKET_ERROR == WSAIoctl(m_Socket, 
			SIO_GET_EXTENSION_FUNCTION_POINTER, 
			&GuidAcceptEx, 
			sizeof(GuidAcceptEx), 
			&m_lpfnAcceptEx, 
			sizeof(LPFN_ACCEPTEX), 
			&dwBytes, 
			NULL, 
			NULL))  
		{  
			TRACE("WSAIoctl δ�ܻ�ȡAcceptEx����ָ�롣�������: %d!!", WSAGetLastError());
			return false;  
		}
		//#ifdef _DEBUG
		// ��ȡGetAcceptExSockAddrs����ָ�룬Ҳ��ͬ��
		if(SOCKET_ERROR == WSAIoctl(m_Socket, 
			SIO_GET_EXTENSION_FUNCTION_POINTER, 
			&GuidGetAcceptExSockAddrs,
			sizeof(GuidGetAcceptExSockAddrs), 
			&m_lpfnGetAcceptExSockAddrs, 
			sizeof(m_lpfnGetAcceptExSockAddrs),   
			&dwBytes, 
			NULL, 
			NULL))  
		{
			TRACE("WSAIoctl δ�ܻ�ȡGuidGetAcceptExSockAddrs����ָ�롣�������: %d!!", WSAGetLastError());
			return false; 
		}
		//#endif
		// Ͷ��AcceptEx I/O����
		// ����ɶ˿�
		if( NULL== CreateIoCompletionPort((HANDLE)m_Socket, m_hIocp,
			(DWORD)(this), 0))  
		{
			TRACE(_T("�� Listen Socket����ɶ˿�ʧ�ܣ��������: %d��"), WSAGetLastError());
			return false;
		}
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		unsigned int nAccept=si.dwNumberOfProcessors*2+2;
		m_OverAccept=new OVERLAPPED_ACCEPT[nAccept];
		for(unsigned int i=0;i<nAccept;i++)
		{
			// �½�һ��IO_CONTEXT
			if(!PostAccept(&m_OverAccept[i]))
			{
				TRACE(_T("PostAccept��������ʧ�ܣ��������: %d��"), WSAGetLastError());
			}
		}
		return true;
	}
	bool Stop()
	{
		if (INVALID_SOCKET!=m_Socket)
		{
			closesocket(m_Socket);
			m_Socket=INVALID_SOCKET;
			return true;
		}
		return false;
	}
};
