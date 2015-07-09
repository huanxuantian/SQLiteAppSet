
// SQLiteMAN1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SQLiteMAN1.h"
#include "SQLiteMAN1Dlg.h"
#include "afxdialogex.h"

#include "sqlite\sqlite3.h"
#include "tool\SQLite3Manager.h"

#include "tool.h"

extern CSQLiteMAN1Dlg* g_pman;
char logmsg[256]={0};
CString d_disp;
int n_Recoder=0;
//extern void SaveLog(char *buf,UINT16 len);
//extern void SaveLog_L(char *buf);
//extern void SaveLog_Hex(char *buf,UINT16 len);
//extern void SaveLog_Hex(UINT8 *buf,UINT16 len);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSQLiteMAN1Dlg 对话框




CSQLiteMAN1Dlg::CSQLiteMAN1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSQLiteMAN1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSQLiteMAN1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDOK,m_btnok);
	DDX_Control(pDX,IDCANCEL,m_btncancel);
	DDX_Control(pDX, IDC_KEY_TEST, m_btntest);
	
	
}

BEGIN_MESSAGE_MAP(CSQLiteMAN1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSQLiteMAN1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_KEY_TEST, &CSQLiteMAN1Dlg::OnBnClickedKeyTest)
END_MESSAGE_MAP()


// CSQLiteMAN1Dlg 消息处理程序

BOOL CSQLiteMAN1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	d_disp.Empty();

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSQLiteMAN1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSQLiteMAN1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		CFont m_font;
		SETFONT(m_font,12);
		dc.SelectObject(m_font);
		dc.DrawText(d_disp,d_disp.GetLength(),CRect(20,10,260,260),DT_NOCLIP|DT_LEFT);

		CDialogEx::OnPaint();
	}
	CRect m_Clrect,m_rect1,m_rect2,m_rect3;
	GetClientRect(m_Clrect);
	m_rect2.bottom = m_Clrect.bottom-20;
	m_rect2.right = m_Clrect.right-20;
	m_rect2.left = m_rect2.right -80;
	m_rect2.top = m_rect2.bottom -20;

	m_rect3.bottom = m_rect2.top - 20;
	m_rect3.left = m_rect2.left;
	m_rect3.right = m_rect2.right;
	m_rect3.top = m_rect3.bottom - 20;

	m_rect1.bottom = m_Clrect.bottom-20;
	m_rect1.right = m_rect2.left-40;
	m_rect1.left = m_rect1.right -80;
	m_rect1.top = m_rect1.bottom -20;



	m_btnok.MoveWindow(m_rect1);
	m_btncancel.MoveWindow(m_rect2);
	m_btntest.MoveWindow(m_rect3);

	GetWindowRect(m_Clrect);
	if (m_Clrect.Width()<m_rect1.Width()*3||m_Clrect.Height()<m_rect1.Height()*3)
	{
		if(m_Clrect.Width()<m_rect1.Width()*3)
			m_Clrect.right=m_Clrect.left + m_rect1.Width()*3;
		if(m_Clrect.Height()<m_rect1.Height()*3)
			m_Clrect.bottom =m_Clrect.top + m_rect1.Height()*3;
	}

	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSQLiteMAN1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


static int LoadMyInfo( void * para, int n_column, char ** column_value, char ** column_name );
void CSQLiteMAN1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	sqlite3 *m_sqlite_db = NULL;

	int result;
	char * errmsg = NULL;

	char msg[256]={0};
	errmsg = msg;

	CString   path=AfxGetApp()->m_pszHelpFilePath;   
	CString   str=AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4); 
	CString tmp_dbname=ReadstrFromInI(_T("SQLITE"),_T("OK"),_T("数据库.db"));
	path+=tmp_dbname;
	wchar_t pw_url[256];
	char p_url[256];
	CString is1;
	

	memcpy(pw_url,path,sizeof(path));

	WideCharToMultiByte( CP_ACP, 0 ,path, -1, p_url,256,NULL,NULL);
		
	d_disp.Empty();
	TRACE0("\n----start----\n");
	sprintf(logmsg,"----start----\n");
	SaveLog_L(logmsg);
	g_pman->showlog();
	TRACE1("RESULT:%s\n",(CString)p_url);
	sprintf(logmsg,"RESULT:%s\n",p_url);
	SaveLog_L(logmsg);
	g_pman->showlog();
	ANSITOUTF8((char*)p_url);
	result = sqlite3_open( (const char *)p_url, &m_sqlite_db );

	//if( result != SQLITE_OK )
	TRACE1("RESULT:%d\n",result);
	sprintf(logmsg,"RESULT:%d\n",result);
	SaveLog_L(logmsg);
	g_pman->showlog();

	n_Recoder=0;
	result = sqlite3_exec( m_sqlite_db, "select * from ND", LoadMyInfo, NULL, &errmsg );
	
	sprintf(logmsg,"RESULT:%d\n",result);
	SaveLog_L(logmsg);
	g_pman->showlog();
	sprintf(logmsg,"n_Recoder:%d\n",n_Recoder);
	SaveLog_L(logmsg);
	g_pman->showlog();
	TRACE0("\n----end----\n");
	sprintf(logmsg,"----end----\n\0");
	g_pman->showlog();
	SaveLog_L(logmsg);
	sqlite3_close(m_sqlite_db);
	//Invalidate(TRUE);
	//CDialogEx::OnOK();
}
void CSQLiteMAN1Dlg::showlog()
{
	d_disp+=(CString)logmsg;
	Invalidate(TRUE);
}

// sqlite 每查到一条记录，就调用一次这个回调
static int LoadMyInfo( void * para, int n_column, char ** column_value, char ** column_name )
{
	//para是你在 sqlite3_exec 里传入的 void * 参数
	//通过para参数，你可以传入一些特殊的指针（比如类指针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
	//n_column是这一条记录有多少个字段 (即这条记录有多少列)
	// char ** column_value 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char * 值，是一个字段内容（用字符串来表示，以/0结尾）
	//char ** column_name 跟 column_value是对应的，表示这个字段的字段名称
	//这里，我不使用 para 参数。忽略它的存在.
	
	int i;
		TRACE1( "%d Recoders column\n", n_column );
		sprintf(logmsg," Recoder.%d :%d column(s)\n",n_Recoder,n_column);
		SaveLog_L(logmsg);

		g_pman->showlog();
	for( i = 0 ; i < n_column; i++ )
	{
		char* c_name=NULL;
		char* c_value=NULL;

		c_name = column_name[i];
		c_value = column_value[i];

		char caTemp_name[256]={0};
		char caTemp_value[256]={0};
		sprintf(caTemp_name,"NAME:%s",c_name);
		UTF8TOANSI((char*) caTemp_name);
		TRACE(caTemp_name);
		sprintf(caTemp_value,"-> VALUE:%s\n",c_value);
		UTF8TOANSI((char*) caTemp_value);
		TRACE(caTemp_value);

		sprintf(logmsg,"%s%s",caTemp_name,caTemp_value);
		SaveLog_L(logmsg);
		printf(logmsg);
		g_pman->showlog();
		
	}
	TRACE( "\n------------------\n");
	sprintf(logmsg,"------------------\n");
	SaveLog_L(logmsg);
	g_pman->showlog();
	n_Recoder++;
	
	return 0;
}

void CSQLiteMAN1Dlg::OnBnClickedKeyTest()
{
	// TODO: Add your control notification handler code here
	CSQLite3Manager *pSQLite;
	d_disp.Empty();
	int effected =0;
	char p_url[256]={0};
	pSQLite = new CSQLite3Manager;

	CString   path = AfxGetApp()->m_pszHelpFilePath;
	CString   str = AfxGetApp()->m_pszExeName;
	path = path.Left(path.GetLength() - str.GetLength() - 4);

	CString tmp1_dbname=ReadstrFromInI(_T("SQLITE"),_T("TEST"),_T("测试.db"));

	d_disp +="DB:";
	d_disp += tmp1_dbname;
	d_disp +="\n";

	if (!pSQLite->OpenConnection(tmp1_dbname, path))
	{
		
		memset(p_url,0,sizeof(p_url));
		WideCharToMultiByte( CP_ACP, 0 ,pSQLite->GetLastError(), -1, p_url,256,NULL,NULL);

		sprintf(logmsg, "\nConnecting To DB Failed :%s",p_url );
		SaveLog_L(logmsg);
		g_pman->showlog();

	}
	//Create DB
	effected = pSQLite->Excute("create table test (seq int(2),name varchar(50));");
	if (effected >= 0)
	{
		sprintf(logmsg, "\nColoumn Effected :%d", effected);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	else
	{
		memset(p_url,0,sizeof(p_url));
		WideCharToMultiByte( CP_ACP, 0 ,pSQLite->GetLastError(), -1, p_url,256,NULL,NULL);
		sprintf(logmsg, "\nError in Query(create) : %s", p_url);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	//Insert Into DB
	effected = pSQLite->Excute("insert into test (seq,name) values (1,'SQLLiteDBtest');");
	if (effected > 0)
	{
		sprintf(logmsg, "\nColoumn Effected :%d", effected);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	else
	{
		memset(p_url,0,sizeof(p_url));
		WideCharToMultiByte( CP_ACP, 0 ,pSQLite->GetLastError(), -1, p_url,256,NULL,NULL);
		sprintf(logmsg, "\nError in Query(insert) : %s", p_url);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	//delete frome DB
	effected = pSQLite->Excute("DELETE  FROM `test` WHERE `rowid`>1;");
	if (effected > 0)
	{
		sprintf(logmsg, "\nColoumn Effected :%d", effected);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	else
	{
		memset(p_url,0,sizeof(p_url));
		WideCharToMultiByte( CP_ACP, 0 ,pSQLite->GetLastError(), -1, p_url,256,NULL,NULL);
		sprintf(logmsg, "\nError in Query(delete) : %s", p_url);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	//Get Data From DB
	IResult *res = pSQLite->ExcuteSelect("Select * from test;");

	if (!res)
	{
		memset(p_url,0,sizeof(p_url));
		WideCharToMultiByte( CP_ACP, 0 ,pSQLite->GetLastError(), -1, p_url,256,NULL,NULL);
		sprintf(logmsg, "\nError in Select : %s", p_url);
		SaveLog_L(logmsg);
		g_pman->showlog();
	}
	else
	{
		d_disp += "\n";
		//Get Column Count
		int i = res->GetColumnCount();
		//Print Column Name
		for (int k = 0; k < i; k++)
		{
			sprintf(logmsg,"%s,", res->NextColomnName(k));
			SaveLog_L(logmsg);
			g_pman->showlog();
		}
		d_disp += "\n";
		//Print Result
		while (res->Next())
		{
			for (int k = 0; k < i; k++)
			{
				sprintf(logmsg, "%s,", res->ColomnData(k));
				SaveLog_L(logmsg);
				g_pman->showlog();
			}
				
			d_disp += "\n";
		}
		Invalidate(TRUE);
		//release Result Data
		res->Release();

	}
	//Insert Heavey Data in DB
	pSQLite->BeginTransaction();

	for (int i = 0; i < 10000; i++)
		pSQLite->Excute("insert into test (seq,name) values (1,'SQLLiteDBtest');");

	pSQLite->CommitTransection();

	delete pSQLite;

}
