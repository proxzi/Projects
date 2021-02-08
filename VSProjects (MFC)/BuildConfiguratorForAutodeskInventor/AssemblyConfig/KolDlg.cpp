// KolDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "KolDlg.h"
#include "afxdialogex.h"


// диалоговое окно CKolDlg

IMPLEMENT_DYNAMIC(CKolDlg, CDialog)

CKolDlg::CKolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_KOL, pParent)
	, Diam(0)
	, DiamVerh(0)
	, ZubVisota(0)
	, Kol_vo_Zubov(0)
	, DiamShest(0)
	, Long2(0)
{

}

CKolDlg::~CKolDlg()
{
}

void CKolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Diam);
	DDX_Text(pDX, IDC_EDIT2, DiamVerh);
	DDX_Text(pDX, IDC_EDIT3, ZubVisota);
	DDX_Text(pDX, IDC_EDIT4, Kol_vo_Zubov);
	DDX_Text(pDX, IDC_EDIT5, DiamShest);
	DDX_Text(pDX, IDC_EDIT6, Long2);
}


BEGIN_MESSAGE_MAP(CKolDlg, CDialog)
END_MESSAGE_MAP()

