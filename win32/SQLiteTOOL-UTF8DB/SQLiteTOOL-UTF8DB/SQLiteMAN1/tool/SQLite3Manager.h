
#if !defined( AFX_SQLITE3MANAGER_H_671B7D65_1FD9_4D43_8DAF_F574018498DB__INCLUDED_)
#define AFX_SQLITE3MANAGER_H_671B7D65_1FD9_4D43_8DAF_F574018498DB__INCLUDED_



//SQLite Header and library
#include "..\\sqlite\\sqlite3.h"


//Struct for Sync database for Multithreading
typedef struct Sync
{
	CRITICAL_SECTION _cs;
	Sync()			 { ::InitializeCriticalSection(&_cs); }
	void LockDB()    { ::EnterCriticalSection(&_cs); }
	void UnLockDB()  { ::LeaveCriticalSection(&_cs); }
	~Sync()          { ::DeleteCriticalSection(&_cs); }
}SyncDB;

/*Interface class for Result data of query*/
class IResult
{
public:
	/*This function return of count of column
	present in result set of last excueted query*/
	virtual int	    GetColumnCount() = 0;

	/*Get the next coloumn name*/
	virtual const char* NextColomnName(int iClmnCount) = 0;

	/*This function returns TRUE if still rows are
	der in result set of last excueted query FALSE
	if no row present*/
	virtual bool  Next() = 0;

	/*Get the next coloumn data*/
	virtual const char*  ColomnData(int clmNum) = 0;

	/*RELEASE all result set as well as RESET all data*/
	virtual void Release() = 0;
};

//SQLite Wrapper Class
class CSQLite3Manager : public IResult
{

public:
	CSQLite3Manager();
	~CSQLite3Manager();

	/*Open Connection*/
	bool OpenConnection(CString DatabaseName, CString DatabaseDir);


	/*Close Connection*/
	void CloseConnection();

	/*Query Wrapper*/
	/*For large insert operation Memory Insert option for SQLLITE dbJournal*/
	void BeginTransaction();
	void CommitTransection();

	/*This Method called when SELECT Query to be excuted.
	Return RESULTSET class pointer on success else NULL of failed*/
	IResult*  ExcuteSelect(const char *Query);

	/*This Method called when INSERT/DELETE/UPDATE Query to be excuted.
	Return UINT count of effected data on success*/
	UINT	    Excute(const char *Query);

	/*Get Last Error of excution*/
	CString GetLastError();

	/*Return TRUE if databse is connected else FALSE*/
	bool  isConnected();


protected:
	/*SQLite Connection Object*/
	typedef struct SQLLITEConnection
	{
		CString		 SQLiteDatabaseName;   //Database Name
		CString		 CSQLite3ManagerPath;		   //Databse File Dir
		sqlite3		 *pCon;				   //SQLite Connection Object
		sqlite3_stmt *pRes;				   //SQLite statement object 
	}SQLITECONNECTIONOBJECT;

	//SQLite Connection Details
	SQLITECONNECTIONOBJECT	 *pSQLiteConn;

	/*Sync Database in Case of Multiple Threads using class object*/
	SyncDB					 *Sync;

	bool	m_bConnected;      /*Is Connected To DB*/
	bool    m_bConsole;	       /*If Console Application*/
	CString  m_strLastError;    /*Last Error String*/
	int	    m_iColumnCount;    /*No.Of Column in Result*/


private:
	/*This function return of count of column
	present in result set of last excueted query*/
	int	    GetColumnCount();

	/*Get the next coloumn name*/
	const char* NextColomnName(int iClmnCount);

	/*This function returns TRUE if still rows are
	der in result set of last excueted query FALSE
	if no row present*/
	bool  Next();

	/*Get the next coloumn data*/
	const char*  ColomnData(int clmNum);

	/*RELEASE all result set as well as RESET all data*/
	void Release();

};

#endif
