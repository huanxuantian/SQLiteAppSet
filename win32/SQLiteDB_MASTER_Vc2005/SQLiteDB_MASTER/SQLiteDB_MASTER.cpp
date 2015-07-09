// SQLiteDB_MASTER.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SQLiteDB_MASTER.h"
#include "SQLiteDB_MASTERDlg.h"

#include "DialgSQLite_SQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDialgSQLite_SQL* g_psqlman;

// CSQLiteDB_MASTERApp

BEGIN_MESSAGE_MAP(CSQLiteDB_MASTERApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSQLiteDB_MASTERApp ����

CSQLiteDB_MASTERApp::CSQLiteDB_MASTERApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSQLiteDB_MASTERApp ����

CSQLiteDB_MASTERApp theApp;


// CSQLiteDB_MASTERApp ��ʼ��

BOOL CSQLiteDB_MASTERApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CSQLiteDB_MASTERDlg dlg;
	//
	//m_pMainWnd = &dlg;

	CDialgSQLite_SQL dlg;

	m_pMainWnd = &dlg;
	g_psqlman = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
