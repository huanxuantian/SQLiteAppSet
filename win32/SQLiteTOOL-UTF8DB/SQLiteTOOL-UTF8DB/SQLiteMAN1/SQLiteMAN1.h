
// SQLiteMAN1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSQLiteMAN1App:
// �йش����ʵ�֣������ SQLiteMAN1.cpp
//

class CSQLiteMAN1App : public CWinApp
{
public:
	CSQLiteMAN1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSQLiteMAN1App theApp;