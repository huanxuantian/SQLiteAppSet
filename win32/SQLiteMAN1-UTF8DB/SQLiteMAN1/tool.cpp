#include "StdAfx.h"
#include "Profile.h"
#include "tool.h"


//profile USAGE:
/*
	g_profile.GetProfileInt("DB","VER",1,THIS_CONFIGFILE);

*/

CProfile g_profile;//全局变量


#define		THIS_CONFIGFILE  "./config.ini"

CString GetInIFileName()
{
	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4);
	path += (CString)THIS_CONFIGFILE;
	return path;
}

BOOL WritestrToInI(CString pare_node,CString child_node,CString strvalue)
{

	if(g_profile.WriteProfileString(pare_node,child_node,strvalue,GetInIFileName()))
		return TRUE;
	else
		return FALSE;
}

CString  ReadstrFromInI(CString pare_node,CString child_node,CString default_value)
{
	return g_profile.GetProfileString(pare_node,child_node,default_value,GetInIFileName());
}

BOOL WriteIntFromInI(const CString strSection, const CString strEntry,const int intvalue)
{
	if(g_profile.WriteProfileInt(strSection,strEntry,intvalue,GetInIFileName()))
		return TRUE;
	else
		return FALSE;
}

UINT32 ReadIntFromInI(const CString strSection, const CString strEntry,const int iDefault)
{
	return g_profile.GetProfileInt(strSection, strEntry,iDefault,GetInIFileName());
}




#define     THIS_LOGFILE            ("./log.txt")

char* GetLogFileName()
{
	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4);
	path += (CString)THIS_LOGFILE;
	char logfile[256];
	memcpy(logfile,path,sizeof(path));
	return (char*)logfile;
}

void SaveLog(char *buf,UINT16 len)
{
	char  path[64] = {0};
	FILE* fp = NULL;
	fp = fopen(GetLogFileName(),"a+b");
	if(!fp)  return ;
	fwrite(buf,1,len,fp);
	fclose(fp);
	return;
}

void SaveLog_L(char *buf)
{
	char temp[100];
	memset(temp,0,sizeof(temp));
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(temp,"%d年%d月%d日 %02d:%02d:%02d %s%s\r\n", 
		systime.wYear,
		systime.wMonth,
		systime.wDay,
		systime.wHour,
		systime.wMinute,
		systime.wSecond,
		buf, "\0");
	SaveLog(temp,strlen(temp));
}



void SaveLog_Hex(char *buf,UINT16 len)
{
	char  path[64] = {0};
	char  tmp[3] = {0};
	FILE* fp = NULL;
	fp = fopen(GetLogFileName(),"a+b");
	if(!fp)  return ;
	for (int i=1; i<len+1; i++) {
		sprintf(tmp,"%02X ",buf[i-1]);
		fwrite(tmp,1,3,fp);
		if (i % 16 == 0)
		{
			fwrite("\r\n",1,2,fp);

		}
	}
	fwrite("\r\n",1,2,fp);
	fclose(fp);
	return;
}
void SaveLog_Hex(UINT8 *buf,UINT16 len)
{
	char  path[64] = {0};
	char  tmp[3] = {0};
	FILE* fp = NULL;
	fp = fopen(GetLogFileName(),"a+b");
	if(!fp)  return ;
	for (int i=1; i<len+1; i++) {
		sprintf(tmp,"%02X ",buf[i-1]);
		fwrite(tmp,1,3,fp);
		if (i % 16 == 0)
		{
			fwrite("\r\n",1,2,fp);

		}
	}
	fwrite("\r\n",1,2,fp);
	fclose(fp);
	return;
}

void ANSITOUTF8(char* szAnsi)
{
	//转换空间预算
	
	int wcsLen =::MultiByteToWideChar(CP_ACP,NULL,szAnsi,strlen(szAnsi),NULL,0);
	wchar_t* wszString = new wchar_t[wcsLen+1];
	//转换数据
	::MultiByteToWideChar(CP_ACP,NULL,szAnsi,strlen(szAnsi),wszString,wcsLen);
	wszString[wcsLen] = '\0';
	
	int utf8Len =WideCharToMultiByte(CP_UTF8,NULL,wszString,-1,NULL,0,NULL,NULL);
	char* utf8Str = new char[utf8Len+1];
	memset(utf8Str, 0, utf8Len + 1);
	WideCharToMultiByte (CP_UTF8, 0, wszString, -1, utf8Str, utf8Len, NULL,NULL);

	 memcpy(szAnsi,utf8Str,utf8Len);
}
void UTF8TOANSI(char* szutf8)
{
	int wcsLen =::MultiByteToWideChar(CP_UTF8,NULL,szutf8,strlen(szutf8),NULL,0);
	wchar_t* wszString = new wchar_t[wcsLen+1];
	::MultiByteToWideChar(CP_UTF8,NULL,szutf8,strlen(szutf8),wszString,wcsLen);
	wszString[wcsLen] = '\0';

	int AnsiLen =WideCharToMultiByte(CP_ACP,NULL,wszString,-1,NULL,0,NULL,NULL);
	char* AnsiStr = new char[AnsiLen+1];
	memset(AnsiStr, 0, AnsiLen + 1);
	WideCharToMultiByte (CP_ACP, 0, wszString, -1, AnsiStr, AnsiLen, NULL,NULL);

	memcpy(szutf8,AnsiStr,AnsiLen);
}
