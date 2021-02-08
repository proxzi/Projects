// ShestDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "ShestDlg.h"
#include "afxdialogex.h"


// диалоговое окно CShestDlg

IMPLEMENT_DYNAMIC(CShestDlg, CDialog)

CShestDlg::CShestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SHEST, pParent)
	, Diam2(0)
	, DiamVerh2(0)
	, ZubVisota2(0)
	, Kol_vo_Zubov2(0)
	, DiamShest2(0)
	, LongB4(0)
{

}

CShestDlg::~CShestDlg()
{
}

void CShestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Diam2);
	DDX_Text(pDX, IDC_EDIT2, DiamVerh2);
	DDX_Text(pDX, IDC_EDIT3, ZubVisota2);
	DDX_Text(pDX, IDC_EDIT4, Kol_vo_Zubov2);
	DDX_Text(pDX, IDC_EDIT5, DiamShest2);
	DDX_Text(pDX, IDC_EDIT6, LongB4);
}


BEGIN_MESSAGE_MAP(CShestDlg, CDialog)
END_MESSAGE_MAP()
 