// sqlite_ce6.cpp : ����Ӧ�ó��������Ϊ��
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

#pragma comment (lib,"./sqlite3/sqlite_wince.lib")
// Csqlite_ce6App

Csqlite_ce6Dlg* core_dlg;

BEGIN_MESSAGE_MAP(Csqlite_ce6App, CWinApp)
END_MESSAGE_MAP()


// Csqlite_ce6App ����
Csqlite_ce6App::Csqlite_ce6App()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Csqlite_ce6App ����
Csqlite_ce6App theApp;

// Csqlite_ce6App ��ʼ��

BOOL Csqlite_ce6App::InitInstance()
{
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    // ��Ӧ�ó����ʼ���ڼ䣬Ӧ����һ�� SHInitExtraControls �Գ�ʼ��
    // ���� Windows Mobile �ض��ؼ����� CAPEDIT �� SIPPREF��
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	Csqlite_ce6Dlg dlg;
	m_pMainWnd = &dlg;
	core_dlg = &dlg;
	

	INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
	//	//  �Ի���Ĵ���
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
