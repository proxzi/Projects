// Val2Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "Val2Dlg.h"
#include "afxdialogex.h"


// диалоговое окно CVal2Dlg

IMPLEMENT_DYNAMIC(CVal2Dlg, CDialog)

CVal2Dlg::CVal2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_VAL2, pParent)
	, DiamShest2(0)
	, DiamPod2(0)
	, DiamOsnov2(0)
	, LongB1(0)
	, LongB2(0)
	, LongB3(0)
	, LongB4(0)
{

}

CVal2Dlg::~CVal2Dlg()
{
}

void CVal2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DiamShest2);
	DDX_Text(pDX, IDC_EDIT2, DiamPod2);
	DDX_Text(pDX, IDC_EDIT3, DiamOsnov2);
	DDX_Text(pDX, IDC_EDIT4, LongB1);
	DDX_Text(pDX, IDC_EDIT5, LongB2);
	DDX_Text(pDX, IDC_EDIT6, LongB3);
	DDX_Text(pDX, IDC_EDIT7, LongB4);
}


BEGIN_MESSAGE_MAP(CVal2Dlg, CDialog)
END_MESSAGE_MAP()
