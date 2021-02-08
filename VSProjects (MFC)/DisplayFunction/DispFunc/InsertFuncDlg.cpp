// InsertFuncDlgh.cpp: файл реализации
//

#include "stdafx.h"
#include "DispFunc.h"
#include "InsertFuncDlg.h"
#include "afxdialogex.h"


// диалоговое окно CInsertFuncDlg

IMPLEMENT_DYNAMIC(CInsertFuncDlg, CDialog)

CInsertFuncDlg::CInsertFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_INSERTFUNCTION, pParent)
	, m_CInputSTR(_T(""))
{

}

CInsertFuncDlg::~CInsertFuncDlg()
{
}

void CInsertFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_CInputSTR);
}


BEGIN_MESSAGE_MAP(CInsertFuncDlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CInsertFuncDlg
