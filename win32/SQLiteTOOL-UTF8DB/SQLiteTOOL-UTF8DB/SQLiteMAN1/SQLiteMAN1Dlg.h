
// SQLiteMAN1Dlg.h : ͷ�ļ�
//

#pragma once


// CSQLiteMAN1Dlg �Ի���
class CSQLiteMAN1Dlg : public CDialogEx
{
// ����
public:
	CSQLiteMAN1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SQLITEMAN1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void showlog();
private:
	CButton m_btnok,m_btncancel,m_btntest;
public:
	afx_msg void OnBnClickedKeyTest();
};
