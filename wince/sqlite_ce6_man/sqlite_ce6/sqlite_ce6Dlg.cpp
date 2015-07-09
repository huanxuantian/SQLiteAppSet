// sqlite_ce6Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sqlite_ce6.h"
#include "sqlite_ce6Dlg.h"

#include "sqlite3/sqlite3.h"

#include "Profile.h"
#include "tool.h"
#include "tool/SQLite3Manager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Csqlite_ce6Dlg 对话框
extern Csqlite_ce6Dlg* core_dlg;

#define SQL_LEN		204800 //200kB

char log_sqlmsg[SQL_LEN]={0};
int n_SQLRecoder=0;
int n_sqllen=0;
char sql_in[SQL_LEN]={0};
wchar_t wsql_in[SQL_LEN]={0};



Csqlite_ce6Dlg::Csqlite_ce6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Csqlite_ce6Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csqlite_ce6Dlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX,IDC_SQL_INPUT,m_sql_input);
	DDX_Control(pDX,IDC_RESAULT_LOGER,m_sql_resault);
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Csqlite_ce6Dlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Csqlite_ce6Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SQL_OK, &Csqlite_ce6Dlg::OnBnClickedSqlOk)
	ON_EN_CHANGE(IDC_SQL_INPUT, &Csqlite_ce6Dlg::OnEnChangeSqlInput)
	ON_BN_CLICKED(IDCANCEL, &Csqlite_ce6Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Csqlite_ce6Dlg 消息处理程序

BOOL Csqlite_ce6Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef WIN32_PLATFORM_WFSP
	if (!m_dlgCommandBar.Create(this) ||
	    !m_dlgCommandBar.InsertMenuBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建 CommandBar\n");
		return FALSE;      // 未能创建
	}
#endif // WIN32_PLATFORM_WFSP
	// TODO: 在此添加额外的初始化代码
	m_sql_input.Clear();
	m_sql_resault.Clear();
	m_sql_input.SetWindowText((LPCTSTR)_T("INSERT INTO `role`(`ID`,`NAME`,`COMMENT`) VALUES (NULL,'admin','admin');\r\nselect * from role;"));

	memset(wsql_in,0,SQL_LEN);
	memset(sql_in,0,SQL_LEN);
	n_sqllen = m_sql_input.GetWindowText((LPTSTR)wsql_in,SQL_LEN);
	int dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wsql_in,-1,NULL,0,NULL,FALSE); 
	WideCharToMultiByte (CP_OEMCP,NULL,wsql_in,-1,sql_in,dwNum,NULL,FALSE); 

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void Csqlite_ce6Dlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_SQLITE_CE6_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_SQLITE_CE6_DIALOG));
	}
}
#endif


void Csqlite_ce6Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//


	sqlite3 *m_sqlite_db = NULL;

	int result;
	char * errmsg = NULL;

	char msg[256]={0};
	errmsg = msg;
#ifdef _WIN32_WCE
	CString   path;
	GetCurrentDirectory(path);
#else
	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4); 
#endif
	CString tmp_dbname=ReadstrFromInI(_T("SQLITE"),_T("SQL"),_T("数据库.db"));
	path+=tmp_dbname;
	//wchar_t pw_url[256];
	char p_url[256];
	CString is1;


	//memcpy(pw_url,path,sizeof(path));

	WideCharToMultiByte( CP_ACP, 0 ,path, -1, p_url,256,NULL,NULL);

	m_sql_loger.Empty();
	TRACE0("\n----start----\n");
	sprintf(log_sqlmsg,"----start----\r\n");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	//TRACE1("RESULT:%s\n",(char*)p_url);
	//printf("RESULT:%s\n",(char*)p_url);
	sprintf(log_sqlmsg,"URL:%s\r\n",p_url);

	TRACE(path);
	TRACE(L"\n");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	ANSITOUTF8((char*)p_url);
	result = sqlite3_open( (const char *)p_url, &m_sqlite_db );

	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	SaveLog_L(log_sqlmsg);
	this->showlog();
	memcpy(sql_in,"DELETE  FROM `role` WHERE `rowid`>5;select * from role",100);

	//memset(p_url,0,256);
	ANSITOUTF8((char*)sql_in);
	n_SQLRecoder=0;
	result = sqlite3_exec( m_sqlite_db, (const char *)sql_in, Callback_Resault, NULL, &errmsg );
	sprintf(log_sqlmsg,"%s\r\n",errmsg);
	core_dlg->showlog();
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	SaveLog_L(log_sqlmsg);
	this->showlog();
	sprintf(log_sqlmsg,"n_Recoder:%d\r\n",n_SQLRecoder);
	SaveLog_L(log_sqlmsg);
	this->showlog();
	TRACE0("\n----end----\n");
	sprintf(log_sqlmsg,"----end----\r\n\0");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	sqlite3_close(m_sqlite_db);
	memset(sql_in,0,sizeof(sql_in));
	//OnOK();
	return;
	//sqlite3 *m_sqlite_db = NULL;

	//int result;
	//char * errmsg = NULL;

	//char msg[256]={0};
	//errmsg = msg;

	//result = sqlite3_open( "/sdmmc/sqlite_ce6/nd.db", &m_sqlite_db );
	//if( result != SQLITE_OK )
	//	TRACE1("ERROR:%d",result);
	//result = sqlite3_exec( m_sqlite_db, "create table MyTable_1( ID integer primary key autoincrement, name nvarchar(32))", NULL, NULL, &errmsg );
	//if( result != SQLITE_OK )
	//	TRACE1("ERROR:%d",result);
	//SaveLog_L(errmsg);
	//result = sqlite3_exec( m_sqlite_db, "insert into MyTable_1( name ) values ( '走路')", 0, 0, &errmsg );
	//if( result != SQLITE_OK )
	//	TRACE1("ERROR:%d",result);
	//SaveLog_L(errmsg);
	//result = sqlite3_exec( m_sqlite_db, "insert into MyTable_1( name) values ('骑单车')", 0, 0, &errmsg );
	//if( result != SQLITE_OK )
	//	TRACE1("ERROR:%d",result);
	//SaveLog_L(errmsg);

	//sqlite3_close(m_sqlite_db);
}



void Csqlite_ce6Dlg::showlog()
{
	m_sql_loger+=(CString)log_sqlmsg;
	//m_sql_resault.ModifyStyle(WS_HSCROLL|ES_MULTILINE|ES_WANTRETURN, 0);
	m_sql_resault.SetWindowText(m_sql_loger);
	if(m_sql_resault.GetLineCount()>6)
		m_sql_resault.ShowScrollBar(TRUE);
	else
		m_sql_resault.ShowScrollBar(FALSE);
	//select * from ND
	Invalidate(TRUE);
}

// sqlite 每查到一条记录，就调用一次这个回调
static int Callback_Resault( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para是你在 sqlite3_exec 里传入的 void * 参数
	//通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
	//n_column是这一条记录有多少个字段 (即这条记录有多少列)
	// char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）
	//char ** column_name 跟 column_value是对应的，表示这个字段的字段名称
	//这里，我不使用 para 参数。忽略它的存在.

	int i;
	TRACE1( "%d Recoders column\r\n", n_column );
	sprintf(log_sqlmsg," Recoder.%d :%d column(s)\r\n",n_SQLRecoder,n_column);
	//SaveLog_L(log_sqlmsg);
	//TRACE(log_sqlmsg);
	core_dlg->showlog();


	for( i = 0 ; i < n_column; i++ )
	{
		char* c_name=NULL;
		char* c_value=NULL;

		c_name = column_name[i];
		c_value = column_value[i];

		char caTemp_name[256]={0};
		char caTemp_value[256]={0};
		sprintf(caTemp_name,"%s",c_name);
		UTF8TOANSI((char*) caTemp_name);
		//TRACE(caTemp_name);
		sprintf(caTemp_value,"=%s,",c_value);
		UTF8TOANSI((char*) caTemp_value);
		//TRACE(caTemp_value);

		sprintf(log_sqlmsg,"%s%s",caTemp_name,caTemp_value);
		SaveLog_L(log_sqlmsg);
		printf(log_sqlmsg);
		//TRACE(log_sqlmsg);
		core_dlg->showlog();


	}
	//TRACE( "\n------------------\n");
	sprintf(log_sqlmsg,"\r\n------------------\r\n");
	SaveLog_L(log_sqlmsg);
	core_dlg->showlog();

	n_SQLRecoder++;

	return 0;
}

void Csqlite_ce6Dlg::OnBnClickedSqlOk()
{
	// TODO: 在此添加控件通知处理程序代码
	sqlite3 *m_sqlite_db = NULL;

	int result;
	char * errmsg = NULL;

	char msg[256]={0};
	errmsg = msg;
#ifdef _WIN32_WCE
	CString   path;
	GetCurrentDirectory(path);
#else
	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4); 
#endif
	CString tmp_dbname=ReadstrFromInI(_T("SQLITE"),_T("SQL"),_T("数据库.db"));
	path+=tmp_dbname;
	//wchar_t pw_url[256];
	char p_url[256];
	CString is1;


	//memcpy(pw_url,path,sizeof(path));

	WideCharToMultiByte( CP_ACP, 0 ,path, -1, p_url,256,NULL,NULL);

	m_sql_loger.Empty();
	TRACE0("\n----start----\n");
	sprintf(log_sqlmsg,"----start----\r\n");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	//TRACE1("RESULT:%s\n",(char*)p_url);
	//printf("RESULT:%s\n",(char*)p_url);
	sprintf(log_sqlmsg,"URL:%s\r\n",p_url);

	TRACE(path);
	TRACE(L"\n");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	ANSITOUTF8((char*)p_url);
	result = sqlite3_open( (const char *)p_url, &m_sqlite_db );

	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	SaveLog_L(log_sqlmsg);
	this->showlog();

	//memset(p_url,0,256);
	ANSITOUTF8((char*)sql_in);
	n_SQLRecoder=0;
	result = sqlite3_exec( m_sqlite_db, (const char *)sql_in, Callback_Resault, NULL, &errmsg );
	sprintf(log_sqlmsg,"%s\r\n",errmsg);
	core_dlg->showlog();
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	SaveLog_L(log_sqlmsg);
	this->showlog();
	sprintf(log_sqlmsg,"n_Recoder:%d\r\n",n_SQLRecoder);
	SaveLog_L(log_sqlmsg);
	this->showlog();
	TRACE0("\n----end----\n");
	sprintf(log_sqlmsg,"----end----\r\n\0");
	SaveLog_L(log_sqlmsg);
	this->showlog();
	sqlite3_close(m_sqlite_db);
}

void Csqlite_ce6Dlg::OnEnChangeSqlInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	if(m_sql_input.GetLineCount()>=2)
		m_sql_input.ShowScrollBar(TRUE);
	else 
		m_sql_input.ShowScrollBar(FALSE);
	memset(wsql_in,0,SQL_LEN);
	memset(sql_in,0,SQL_LEN);
	n_sqllen = m_sql_input.GetWindowText((LPTSTR)wsql_in,SQL_LEN);
	int dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wsql_in,-1,NULL,0,NULL,FALSE); 
	WideCharToMultiByte (CP_OEMCP,NULL,wsql_in,-1,sql_in,dwNum,NULL,FALSE); 
}

void Csqlite_ce6Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
