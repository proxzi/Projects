// Val1Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "Val1Dlg.h"
#include "afxdialogex.h"


// диалоговое окно CVal1Dlg

IMPLEMENT_DYNAMIC(CVal1Dlg, CDialog)

CVal1Dlg::CVal1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_VAL1, pParent)
	, DiamPod(0)
	, DiamOsnov(0)
	, DiamShest(0)
	, Long1(0)
	, Long2(0)
	, Long3(0)
{
}

CVal1Dlg::~CVal1Dlg()
{
}

void CVal1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DiamPod);
	DDX_Text(pDX, IDC_EDIT2, DiamOsnov);
	DDX_Text(pDX, IDC_EDIT3, DiamShest);
	DDX_Text(pDX, IDC_EDIT4, Long1);
	DDX_Text(pDX, IDC_EDIT5, Long2);
	DDX_Text(pDX, IDC_EDIT6, Long3);
}


BEGIN_MESSAGE_MAP(CVal1Dlg, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CVal1Dlg



BOOL CVal1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
