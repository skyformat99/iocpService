/*********************************˵��*********************************
1.֧�ֶ��߳� 1~100
2.Ч��(1����)
 A.���߳�:13853ms:72.18657pcs/ms
 B:10�߳�:6661ms:150.1276pcs/ms,
 C.100�߳�:7301ms:136.9675pcs/ms
3.ʹ�÷���
 ����ʹ��ȫ�ֶ���
4.���ϸ��
 �ļ�����,�Զ�����,��������
*********************************˵��*********************************/
#pragma once
#include <time.h>
#include <share.h>
#include  <io.h>
#include <sys/stat.h>
//#include <fstream>
#define log_buf_size 1024

class CFileLog
{
public:
	CFileLog(void)
	: m_nPath(0)
	, m_CurDay(0)
	, m_nLogLevel(2)
	,pfp(NULL)
	{
		// ��ʼ���ٽ���
		InitializeCriticalSection(&m_cs);
		GetModuleFileNameA(GetSelfModuleHandle(), m_szPath, MAX_PATH );
		int nLen=strlen(m_szPath);
		for (int i=nLen;i>0;i--) //ȥģ����
		{
			if (m_szPath[i]=='\\'||m_szPath[i]=='/')
			{
				strcpy_s(m_szPath+i+1,MAX_PATH-i-1,"Log\\");// ���Log�ļ���
				break;
			}
		}
		m_nPath=strlen(m_szPath);
		if (GetFileAttributesA(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//Ŀ¼�����ڴ���
		{
			CreateDirectoryA(m_szPath, NULL);
		}
	}
	~CFileLog(void)
	{
		if(pfp!=NULL)
		{
			fclose(pfp);
		}
		// �ͷ��ٽ���
		DeleteCriticalSection(&m_cs);
	}
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	}
private:
	// Log·��
	char m_szPath[MAX_PATH];
	// Log·������
	int m_nPath;
	FILE* pfp;
	// ��ǰСʱ
	int m_CurDay;
	int m_nLogLevel;// 0 ��������,1 һ�����,2..������Ϣ
	// �ٽ���
	CRITICAL_SECTION m_cs;
public:
	// ����Log����
	int SetLogLevel(int nLevel)
	{
		m_nLogLevel=nLevel;
		return m_nLogLevel;
	}
	bool GetLogLevel(int nLevel)
	{
		return nLevel>m_nLogLevel;
	}
	// дLog
	bool WriteLog(int nLevel,char* Fmt,...)
	{
		if (nLevel>m_nLogLevel)
		{
			return false;
		}
		try
		{
			char sztBuf[log_buf_size];
			time_t curTime;
			struct tm mt;
			curTime = time(NULL);
			localtime_s(&mt,&curTime);
			strftime(sztBuf,log_buf_size,"%Y-%m-%d %H:%M:%S Level:",&mt);
			int nLen=strlen(sztBuf);
			sprintf_s(sztBuf+nLen,log_buf_size-nLen,"%d,",nLevel);
			nLen=strlen(sztBuf);
			va_list argptr;          //�����ַ����ĸ�ʽ
			va_start(argptr, Fmt);
			_vsnprintf_s(sztBuf+nLen, log_buf_size-nLen,_TRUNCATE, Fmt, argptr);
			va_end(argptr);
			if(mt.tm_hour!=m_CurDay) // ÿСʱһ��Log�ļ�
			{
				if (GetFileAttributesA(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//Ŀ¼�����ڴ���
				{
					if(!CreateDirectoryA(m_szPath, NULL))
					{
						return false;
					}
				}
				m_CurDay=mt.tm_hour;	
				char szLogFile[MAX_PATH]={0};
				strcpy_s(szLogFile,MAX_PATH,m_szPath);
				strftime(szLogFile+m_nPath,MAX_PATH-m_nPath,"%Y%m%d%H.log",&mt);
				if (NULL!=pfp)
				{
					fclose(pfp);
					pfp=NULL;
				}
				pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //����ӵķ�ʽ������ļ�
				if (NULL==pfp)
				{
					return false;
				}
			}
			fprintf(pfp,"%s\n",sztBuf);
			fflush(pfp);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	/*************************************
	֧��д�븲��,���·ݸ���
	**************************************/
	bool WriteLog(char* szLog,struct tm* mt)
	{
			EnterCriticalSection(&m_cs);
			if(!pfp||mt->tm_mday!=m_CurDay) // ÿСʱһ��Log�ļ�
			{
				m_CurDay=mt->tm_mday;	
				char szLogFile[MAX_PATH]={0};
				strcpy_s(szLogFile,MAX_PATH,m_szPath);
				strftime(szLogFile+m_nPath,MAX_PATH-m_nPath,"%d.log",mt);
				// �ж��ļ��Ƿ����
				if (NULL!=pfp)
				{
					fclose(pfp);
					pfp=NULL;
				}
				if(_taccess(szLogFile,0)!= -1 )// �ļ�����  
				{
					// ��ȡ�ļ��д���ʱ��  
					struct stat sb;
					sb.st_size=sizeof(sb);
					stat(szLogFile,&sb);
					if (sb.st_ctime<time(NULL)-86400)
					{
						DeleteFile(szLogFile);
					}
				}
				pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //����ӵķ�ʽ������ļ�
				if (NULL==pfp)
				{
					LeaveCriticalSection(&m_cs);
					return false;
				}
			}
			if(fprintf(pfp,"%s\n",szLog)<0)
			{
				fclose(pfp);
				pfp=NULL;
				LeaveCriticalSection(&m_cs);
				return false;
			}
			if(EOF==fflush(pfp))
			{
				fclose(pfp);
				pfp=NULL;
			}
			LeaveCriticalSection(&m_cs);
		return true;
	}
};
