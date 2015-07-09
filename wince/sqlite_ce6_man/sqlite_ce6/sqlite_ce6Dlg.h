// sqlite_ce6Dlg.h : 头文件
//

#pragma once

// Csqlite_ce6Dlg 对话框
class Csqlite_ce6Dlg : public CDialog
{
// 构造
public:
	Csqlite_ce6Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SQLITE_CE6_DIALOG };

#ifdef WIN32_PLATFORM_WFSP
protected:  // 控件条嵌入成员
	CCommandBar m_dlgCommandBar;
#endif // WIN32_PLATFORM_WFSP

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
private:
	CEdit m_sql_input,m_sql_resault;
	CString m_sql_string,m_sql_loger;

public:
	afx_msg void OnBnClickedOk();
	void showlog();
	afx_msg void OnBnClickedSqlOk();
	afx_msg void OnEnChangeSqlInput();
	afx_msg void OnBnClickedCancel();
};
static int Callback_Resault( void * para, int n_column, char ** column_value, char ** column_name );
