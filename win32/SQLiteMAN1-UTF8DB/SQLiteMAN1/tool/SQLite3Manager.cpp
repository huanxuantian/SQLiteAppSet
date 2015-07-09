#include "stdafx.h"
#include "SQLite3Manager.h"

#include "..\sqlite\sqlite3.h"

#include "..\tool.h"


CSQLite3Manager::CSQLite3Manager(void)
{
	sqlite3 *m_sqlite_db = NULL;

	int result;
	char * errmsg = NULL;

	char msg[256]={0};
	errmsg = msg;

	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4); 

	//WritestrToInI(_T("SQLITE"),_T("ND"),_T("nd.db"));

	CString tmp_dbname=ReadstrFromInI(_T("SQLITE"),_T("ND"),_T("nd.db"));
	path += tmp_dbname;
	wchar_t pw_url[256];
	char p_url[256];
	CString is1;

	char logmsg[256]={0};

	memcpy(pw_url,path,sizeof(path));
	WideCharToMultiByte( CP_ACP, 0 ,path, -1, p_url,256,NULL,NULL);
	ANSITOUTF8((char*)p_url);
	TRACE0("\n----start----\n");
	sprintf(logmsg,"----start----");
	SaveLog_L(logmsg);
	TRACE1("RESULT:%s\n",(CString)p_url);

	sprintf(logmsg,"RESULT:%s",p_url);
	SaveLog_L(logmsg);

	result = sqlite3_open( (const char *)p_url, &m_sqlite_db );

	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(logmsg,"RESULT:%d",result);
	SaveLog_L(logmsg);
	memset(p_url,0,256);

	//result = sqlite3_key(m_sqlite_db,"529254",6);

	result = sqlite3_exec( m_sqlite_db, "create table ND( ID integer primary key autoincrement, name nvarchar(32))", NULL, NULL, &errmsg );
	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(logmsg,"RESULT:%d",result);
	SaveLog_L(logmsg);
	if( result != SQLITE_OK )
		SaveLog_L(errmsg);
	if( result == SQLITE_OK )//数据表不存在时，第一次创建数据表
	{
		//初始化表内容
		is1.Empty();
		is1=_T("insert into ND( name ) values ( '步行')");
		WideCharToMultiByte( CP_ACP, 0 ,is1, -1, p_url,256,NULL,NULL);
		ANSITOUTF8((char*)p_url);

		result = sqlite3_exec( m_sqlite_db, p_url, 0, 0, &errmsg );
		//if( result != SQLITE_OK )
		TRACE1("RESULT:%d\n",result);
		sprintf(logmsg,"RESULT:%d",result);
		SaveLog_L(logmsg);
		is1.Empty();
		is1=_T("insert into ND( name) values ('骑车')");
		WideCharToMultiByte( CP_ACP, 0 ,is1, -1, p_url,256,NULL,NULL);
		ANSITOUTF8((char*)p_url);

		result = sqlite3_exec( m_sqlite_db, p_url, 0, 0, &errmsg );
		//if( result != SQLITE_OK )
		TRACE1("RESULT:%d\n",result);
		sprintf(logmsg,"RESULT:%d",result);
		SaveLog_L(logmsg);
	}

	TRACE0("\n----end----\n");
	sprintf(logmsg,"----end----");
	SaveLog_L(logmsg);
	sqlite3_close(m_sqlite_db);
}


CSQLite3Manager::~CSQLite3Manager(void)
{
}




