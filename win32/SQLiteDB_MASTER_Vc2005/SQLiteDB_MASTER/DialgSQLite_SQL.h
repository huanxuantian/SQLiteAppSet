#pragma once


// CDialgSQLite_SQL 对话框

class CDialgSQLite_SQL : public CDialog
{
	DECLARE_DYNAMIC(CDialgSQLite_SQL)

public:
	CDialgSQLite_SQL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgSQLite_SQL();

// 对话框数据
	enum { IDD = IDD_DLG_SQL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_sql_input,m_sql_resault;
	CButton m_btn_ok,m_btn_cancel;
	CString m_sql_string,m_sql_loger;
	
public:
	void showlog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeSqlInput();
	afx_msg void OnEnChangeResaultLoger();
	afx_msg void OnBnClickedSqlLoad();
};
