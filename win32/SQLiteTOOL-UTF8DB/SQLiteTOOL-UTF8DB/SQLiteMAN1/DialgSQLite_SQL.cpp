// DialgSQLite_SQL.cpp : 实现文件
//

#include "stdafx.h"
#include "SQLiteMAN1.h"
#include "DialgSQLite_SQL.h"
#include "afxdialogex.h"


#include "sqlite\sqlite3.h"

#include "tool.h"

extern CDialgSQLite_SQL* g_psqlman;

// CDialgSQLite_SQL 对话框

IMPLEMENT_DYNAMIC(CDialgSQLite_SQL, CDialog)

CDialgSQLite_SQL::CDialgSQLite_SQL(CWnd* pParent /*=NULL*/)
	: CDialog(CDialgSQLite_SQL::IDD, pParent)
{

}

CDialgSQLite_SQL::~CDialgSQLite_SQL()
{
}

void CDialgSQLite_SQL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SQL_INPUT,m_sql_input);
	DDX_Control(pDX,IDC_RESAULT_LOGER,m_sql_resault);
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_cancel);
}


BEGIN_MESSAGE_MAP(CDialgSQLite_SQL, CDialog)
	ON_BN_CLICKED(IDOK, &CDialgSQLite_SQL::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialgSQLite_SQL::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SQL_INPUT, &CDialgSQLite_SQL::OnEnChangeSqlInput)
	ON_EN_CHANGE(IDC_RESAULT_LOGER, &CDialgSQLite_SQL::OnEnChangeResaultLoger)
	ON_BN_CLICKED(IDC_SQL_LOAD, &CDialgSQLite_SQL::OnBnClickedSqlLoad)
END_MESSAGE_MAP()


BOOL CDialgSQLite_SQL::OnInitDialog()
{
		CDialog::OnInitDialog();
		//初始化处理
		m_sql_input.Clear();
		m_sql_resault.Clear();
		//m_sql_input.ModifyStyle(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE|ES_WANTRETURN, 0);
		//m_sql_resault.ModifyStyle(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE|ES_WANTRETURN, 0);
		return TRUE;
}


// CDialgSQLite_SQL 消息处理程序

char log_sqlmsg[1000]={0};
int n_SQLRecoder=0;
int n_sqllen=0;
char sql_in[1000]={0};
wchar_t wsql_in[1000]={0};
static int Callback_Resault( void * para, int n_column, char ** column_value, char ** column_name );
void CDialgSQLite_SQL::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	if(n_sqllen<=0)return;

	sqlite3 *m_sqlite_db = NULL;

	int result;
	char * errmsg = NULL;

	char msg[256]={0};
	errmsg = msg;

	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4); 
	CString tmp_dbname=ReadstrFromInI(_T("SQLITE"),_T("SQL"),_T("数据库.db"));
	path+=tmp_dbname;
	wchar_t pw_url[256];
	char p_url[256];
	CString is1;


	memcpy(pw_url,path,sizeof(path));

	WideCharToMultiByte( CP_ACP, 0 ,path, -1, p_url,256,NULL,NULL);

	m_sql_loger.Empty();
	TRACE0("\n----start----\n");
	sprintf(log_sqlmsg,"----start----\r\n");
	//SaveLog_L(log_sqlmsg);
	this->showlog();
	TRACE1("RESULT:%s\n",(CString)p_url);
	sprintf(log_sqlmsg,"RESULT:%s\r\n",p_url);
	//SaveLog_L(log_sqlmsg);
	this->showlog();
	ANSITOUTF8((char*)p_url);
	result = sqlite3_open( (const char *)p_url, &m_sqlite_db );

	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	//SaveLog_L(log_sqlmsg);
	this->showlog();


	//memset(p_url,0,256);
	ANSITOUTF8((char*)sql_in);
	n_SQLRecoder=0;
	result = sqlite3_exec( m_sqlite_db, (const char *)sql_in, Callback_Resault, NULL, &errmsg );
	sprintf(log_sqlmsg,"%s\r\n",errmsg);
	g_psqlman->showlog();
	sprintf(log_sqlmsg,"RESULT:%d\r\n",result);
	//SaveLog_L(log_sqlmsg);
	this->showlog();
	sprintf(log_sqlmsg,"n_Recoder:%d\r\n",n_SQLRecoder);
	//SaveLog_L(log_sqlmsg);
	this->showlog();
	TRACE0("\n----end----\n");
	sprintf(log_sqlmsg,"----end----\r\n\0");
	//SaveLog_L(log_sqlmsg);
	this->showlog();
	sqlite3_close(m_sqlite_db);

}

void CDialgSQLite_SQL::showlog()
{
	m_sql_loger+=(CString)log_sqlmsg;
	//m_sql_resault.ModifyStyle(WS_HSCROLL|ES_MULTILINE|ES_WANTRETURN, 0);
	m_sql_resault.SetWindowText(m_sql_loger);
	if(m_sql_resault.GetLineCount()>8)
		m_sql_resault.ShowScrollBar(SB_VERT);
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
	g_psqlman->showlog();


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
		TRACE(caTemp_name);
		sprintf(caTemp_value,"=%s,",c_value);
		UTF8TOANSI((char*) caTemp_value);
		TRACE(caTemp_value);

		sprintf(log_sqlmsg,"%s%s",caTemp_name,caTemp_value);
		//SaveLog_L(log_sqlmsg);
		printf(log_sqlmsg);
		g_psqlman->showlog();


	}
	TRACE( "\n------------------\n");
	sprintf(log_sqlmsg,"\r\n------------------\r\n");
	//SaveLog_L(log_sqlmsg);
	g_psqlman->showlog();

	n_SQLRecoder++;

	return 0;
}


void CDialgSQLite_SQL::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CDialgSQLite_SQL::OnEnChangeSqlInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(m_sql_input.GetLineCount()>3)
		m_sql_input.ShowScrollBar(SB_VERT);
	memset(wsql_in,0,1000);
	memset(sql_in,0,1000);
	n_sqllen = m_sql_input.GetWindowText((LPTSTR)wsql_in,1000);
	int dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wsql_in,-1,NULL,0,NULL,FALSE); 
	WideCharToMultiByte (CP_OEMCP,NULL,wsql_in,-1,sql_in,dwNum,NULL,FALSE); 

	//m_sql_input.

	//m_sql_string = ;
}


void CDialgSQLite_SQL::OnEnChangeResaultLoger()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
}


void CDialgSQLite_SQL::OnBnClickedSqlLoad()
{
	// TODO: 在此添加控件通知处理程序代码

}
