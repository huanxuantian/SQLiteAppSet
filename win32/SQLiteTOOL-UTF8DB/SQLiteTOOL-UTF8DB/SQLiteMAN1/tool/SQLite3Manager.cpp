#include "stdafx.h"
#include "SQLite3Manager.h"

#include <Windows.h>

#include "..\sqlite\sqlite3.h"
#pragma comment (lib,"sqlite\\sqlite_win32_dll.lib")

#include "..\tool.h"


CSQLite3Manager::CSQLite3Manager()
{
	m_bConnected = false;
	pSQLiteConn = new SQLITECONNECTIONOBJECT();
	Sync = new SyncDB();
}


CSQLite3Manager::~CSQLite3Manager()
{
	CloseConnection();
	delete pSQLiteConn;
	delete Sync;
}


void CSQLite3Manager::CloseConnection()
{
	if (pSQLiteConn->pCon)
		sqlite3_close(pSQLiteConn->pCon);
}

CString CSQLite3Manager::GetLastError()
{
	return m_strLastError;
}

bool   CSQLite3Manager::isConnected()
{
	return m_bConnected;
}

bool CSQLite3Manager::OpenConnection(CString DatabaseName, CString DatabaseDir)
{
	pSQLiteConn->SQLiteDatabaseName = DatabaseName;
	pSQLiteConn->CSQLite3ManagerPath = DatabaseDir;

	m_bConnected = true;

	CString db = pSQLiteConn->SQLiteDatabaseName;
	CString dir = pSQLiteConn->CSQLite3ManagerPath;
	CString path = dir + db;
	char p_url[256];

	::WideCharToMultiByte(CP_ACP, 0, path, -1, p_url, 256, NULL, NULL);
	ANSITOUTF8((char*)p_url);

	int rc = sqlite3_open((const char *)p_url, &(pSQLiteConn->pCon));

	m_strLastError = (CString)sqlite3_errmsg(pSQLiteConn->pCon);

	if (!rc)
	{
		if (m_strLastError.FindOneOf(_T("not an error")) == -1)
			m_bConnected = false;
	}


	return m_bConnected;
}

void CSQLite3Manager::BeginTransaction()
{
	sqlite3_exec(pSQLiteConn->pCon, "BEGIN TRANSACTION", NULL, NULL, NULL);
}

void CSQLite3Manager::CommitTransection()
{
	sqlite3_exec(pSQLiteConn->pCon, "COMMIT TRANSACTION", NULL, NULL, NULL);
}

IResult*  CSQLite3Manager::ExcuteSelect(const char *Query)
{
	if (!isConnected())
		return NULL;
	//ANSITOUTF8((char*)Query);
	Sync->LockDB();

	if (sqlite3_prepare_v2(pSQLiteConn->pCon, Query, -1, &pSQLiteConn->pRes, NULL) != SQLITE_OK)
	{
		m_strLastError = sqlite3_errmsg(pSQLiteConn->pCon);
		sqlite3_finalize(pSQLiteConn->pRes);
		Sync->UnLockDB();
		return NULL;
	}
	else
	{
		m_iColumnCount = sqlite3_column_count(pSQLiteConn->pRes);
		IResult *ires = this;
		return ires;
	}
}

UINT CSQLite3Manager::Excute(const char *Query)
{
	if (!isConnected())
		return NULL;
	m_strLastError = "";
	//ANSITOUTF8((char*)Query);
	char* err = "";

	if (sqlite3_exec(pSQLiteConn->pCon, Query, NULL, 0, &err) != SQLITE_OK)
	{
		m_strLastError = sqlite3_errmsg(pSQLiteConn->pCon);
		return 0;
	}
	return sqlite3_total_changes(pSQLiteConn->pCon);
}


/*Result Set Definations*/
int	CSQLite3Manager::GetColumnCount()
{
	return m_iColumnCount;
}

const char* CSQLite3Manager::NextColomnName(int iClmnCount)
{
	if (iClmnCount > m_iColumnCount)
		return "";
	const char* queryresault = NULL;
	queryresault = sqlite3_column_name(pSQLiteConn->pRes, iClmnCount);
	return queryresault;
}

bool CSQLite3Manager::Next()
{
	return (sqlite3_step(pSQLiteConn->pRes) == SQLITE_ROW) ? true : false;
}

const char*  CSQLite3Manager::ColomnData(int clmNum)
{
	if (clmNum > m_iColumnCount)
		return "";
	const char* queryresault=NULL;
	queryresault = (const char*)sqlite3_column_text(pSQLiteConn->pRes, clmNum);
	//UTF8TOANSI((char*)queryresault);
	return ((const char*)queryresault);
}

void CSQLite3Manager::Release()
{
	sqlite3_finalize(pSQLiteConn->pRes);
	m_iColumnCount = 0;
	m_strLastError = "";
	Sync->UnLockDB();
}






