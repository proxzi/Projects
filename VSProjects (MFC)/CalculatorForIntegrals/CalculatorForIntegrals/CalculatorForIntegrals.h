
// CalculatorForIntegrals.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCalculatorForIntegralsApp:
// О реализации данного класса см. CalculatorForIntegrals.cpp
//

class CCalculatorForIntegralsApp : public CWinApp
{
public:
	CCalculatorForIntegralsApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCalculatorForIntegralsApp theApp;