
// AssemblyConfig.h : главный файл заголовка для приложения AssemblyConfig
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CAssemblyConfigApp:
// О реализации данного класса см. AssemblyConfig.cpp
//

class CAssemblyConfigApp : public CWinApp
{
public:
	CAssemblyConfigApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAssemblyConfigApp theApp;
