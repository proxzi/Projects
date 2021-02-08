
// DispFunc.h : главный файл заголовка для приложения DispFunc
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CDispFuncApp:
// О реализации данного класса см. DispFunc.cpp
//

class CDispFuncApp : public CWinApp
{
public:
	CDispFuncApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDispFuncApp theApp;
