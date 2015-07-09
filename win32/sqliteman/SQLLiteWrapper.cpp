//#include "StdAfx.h"
#include "SQLLiteWrapper.h"


SQLiteDB::SQLiteDB()
{
	m_bConnected=false;
	pSQLiteConn = new SQLITECONNECTIONOBJECT();
	Sync		= new SyncDB();
}


SQLiteDB::~SQLiteDB()
{
	CloseConnection();
	delete pSQLiteConn;
	delete Sync;
}


void SQLiteDB::CloseConnection()
{
	if(pSQLiteConn->pCon)
		sqlite3_close(pSQLiteConn->pCon);
}

string SQLiteDB::GetLastError()
{
	return m_strLastError;
}

bool   SQLiteDB::isConnected()
{
	return m_bConnected;
}

bool SQLiteDB::OpenConnection(string DatabaseName,string DatabaseDir)
{
	pSQLiteConn->SQLiteDatabaseName = DatabaseName;
	pSQLiteConn->SQLiteDBPath	    = DatabaseDir;
	
	m_bConnected = true;

	string db=pSQLiteConn->SQLiteDatabaseName;
	string dir=pSQLiteConn->SQLiteDBPath;
	string path=dir.append(db);

	int rc = sqlite3_open(path.c_str(), &(pSQLiteConn->pCon));

	m_strLastError =(string)sqlite3_errmsg(pSQLiteConn->pCon);
	
	if(!rc)
	{
		if(m_strLastError.find("not an error") == string::npos)
			m_bConnected = false;
	}


	return m_bConnected;
}

void SQLiteDB::BeginTransaction()
{
	sqlite3_exec(pSQLiteConn->pCon, "BEGIN TRANSACTION", NULL, NULL,NULL);
}

void SQLiteDB::CommitTransection()
{
	sqlite3_exec(pSQLiteConn->pCon, "COMMIT TRANSACTION", NULL, NULL,NULL);
}

IResult*  SQLiteDB::ExcuteSelect(const char *Query)
{
	if(!isConnected())
		return NULL;

	Sync->LockDB();

	if(sqlite3_prepare_v2(pSQLiteConn->pCon,Query,-1, &pSQLiteConn->pRes, NULL) != SQLITE_OK)
		{
			m_strLastError=sqlite3_errmsg(pSQLiteConn->pCon);		
			sqlite3_finalize(pSQLiteConn->pRes);
			Sync->UnLockDB();
			return NULL;
		}
		else
		{			
			m_iColumnCount   =sqlite3_column_count(pSQLiteConn->pRes);
			IResult *ires=this;
			return ires;
		}
}

UINT SQLiteDB::Excute(const char *Query)
{
	if(!isConnected())
		return NULL;
	m_strLastError="";
	
	char* err="";
	
	if(sqlite3_exec(pSQLiteConn->pCon, Query, NULL, 0, &err) != SQLITE_OK)
	{
		m_strLastError=sqlite3_errmsg(pSQLiteConn->pCon);
		return 0;
	}
	return sqlite3_total_changes(pSQLiteConn->pCon);	
}


/*Result Set Definations*/
int	SQLiteDB::GetColumnCount()
{
	return m_iColumnCount;
}

const char* SQLiteDB::NextColomnName(int iClmnCount)
{
	if(iClmnCount > m_iColumnCount)
		return "";
	return sqlite3_column_name(pSQLiteConn->pRes,iClmnCount);
}

bool SQLiteDB:: Next()
{
	return (sqlite3_step(pSQLiteConn->pRes)==SQLITE_ROW) ? true : false;
}

const char*  SQLiteDB::ColomnData(int clmNum)
{
	if(clmNum > m_iColumnCount)
		return "";
	return ((const char*)sqlite3_column_text(pSQLiteConn->pRes,clmNum));
}

void SQLiteDB::Release()
{
	sqlite3_finalize(pSQLiteConn->pRes);
	m_iColumnCount=0;
	m_strLastError="";
	Sync->UnLockDB();
}


