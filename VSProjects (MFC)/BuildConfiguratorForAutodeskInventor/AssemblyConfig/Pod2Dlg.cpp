// Pod2Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "Pod2Dlg.h"
#include "afxdialogex.h"


// диалоговое окно CPod2Dlg

IMPLEMENT_DYNAMIC(CPod2Dlg, CDialog)

CPod2Dlg::CPod2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_POD2, pParent)
	, DiamVnesh2(0)
	, Kol_Vo_Shar2(0)
	, DiamShar2(0)
	, DiamPod2(0)
	, LongB3(0)
{

}

CPod2Dlg::~CPod2Dlg()
{
}

void CPod2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DiamVnesh2);
	DDX_Text(pDX, IDC_EDIT2, Kol_Vo_Shar2);
	DDX_Text(pDX, IDC_EDIT3, DiamShar2);
	DDX_Text(pDX, IDC_EDIT5, DiamPod2);
	DDX_Text(pDX, IDC_EDIT6, LongB3);
}


BEGIN_MESSAGE_MAP(CPod2Dlg, CDialog)
END_MESSAGE_MAP()
