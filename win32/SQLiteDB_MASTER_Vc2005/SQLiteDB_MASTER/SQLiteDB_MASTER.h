// SQLiteDB_MASTER.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSQLiteDB_MASTERApp:
// �йش����ʵ�֣������ SQLiteDB_MASTER.cpp
//

class CSQLiteDB_MASTERApp : public CWinApp
{
public:
	CSQLiteDB_MASTERApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSQLiteDB_MASTERApp theApp;