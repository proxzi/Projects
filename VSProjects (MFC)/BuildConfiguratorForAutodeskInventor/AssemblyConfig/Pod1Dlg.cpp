// Pod1Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "Pod1Dlg.h"
#include "afxdialogex.h"


// диалоговое окно CPod1Dlg

IMPLEMENT_DYNAMIC(CPod1Dlg, CDialog)

CPod1Dlg::CPod1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_POD1, pParent)
	, DiamVnesh(0)
	, Kol_Vo_Shar(0)
	, DiamShar(0)
	, DiamPod(0)
	, Long1(0)
{

}

CPod1Dlg::~CPod1Dlg()
{
}

void CPod1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DiamVnesh);
	DDX_Text(pDX, IDC_EDIT2, Kol_Vo_Shar);
	DDX_Text(pDX, IDC_EDIT3, DiamShar);
	DDX_Text(pDX, IDC_EDIT5, DiamPod);
	DDX_Text(pDX, IDC_EDIT6, Long1);
}


BEGIN_MESSAGE_MAP(CPod1Dlg, CDialog)
END_MESSAGE_MAP()
