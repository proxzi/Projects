
// AssemblyConfig.h : ������� ���� ��������� ��� ���������� AssemblyConfig
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CAssemblyConfigApp:
// � ���������� ������� ������ ��. AssemblyConfig.cpp
//

class CAssemblyConfigApp : public CWinApp
{
public:
	CAssemblyConfigApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAssemblyConfigApp theApp;
