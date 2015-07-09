// SQLiteDB_MASTER.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CSQLiteDB_MASTERApp:
// 有关此类的实现，请参阅 SQLiteDB_MASTER.cpp
//

class CSQLiteDB_MASTERApp : public CWinApp
{
public:
	CSQLiteDB_MASTERApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSQLiteDB_MASTERApp theApp;