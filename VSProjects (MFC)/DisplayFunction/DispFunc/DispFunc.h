
// DispFunc.h : ������� ���� ��������� ��� ���������� DispFunc
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CDispFuncApp:
// � ���������� ������� ������ ��. DispFunc.cpp
//

class CDispFuncApp : public CWinApp
{
public:
	CDispFuncApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDispFuncApp theApp;
