
// CalculatorForIntegrals.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CCalculatorForIntegralsApp:
// � ���������� ������� ������ ��. CalculatorForIntegrals.cpp
//

class CCalculatorForIntegralsApp : public CWinApp
{
public:
	CCalculatorForIntegralsApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CCalculatorForIntegralsApp theApp;