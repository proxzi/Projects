// SetParamDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "DispFunc.h"
#include "SetParamDlg.h"
#include "afxdialogex.h"
#include <fstream>

// диалоговое окно CSetParamDlg

IMPLEMENT_DYNAMIC(CSetParamDlg, CDialog)

CSetParamDlg::CSetParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALSETPARAM, pParent)
{
	m_cSPPointX.RemoveAll();
	m_cSPPointY.RemoveAll();
	m_CMFC_lines.EnableOtherButton(_T("Доп. цвета"),TRUE,TRUE);
	m_CMFC_points.EnableOtherButton(_T("Доп. цвета"), FALSE, TRUE);
	m_CMFCPointColor = RGB(255, 0, 0);
	m_CMFCLineColor = RGB(0, 255, 0);
}

CSetParamDlg::~CSetParamDlg()
{
}

void CSetParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORPOINTS, m_CMFC_points);
	DDX_Control(pDX, IDC_MFCCOLORLINES, m_CMFC_lines);
	m_CMFC_lines.EnableOtherButton(_T("Доп. цвета"), FALSE, TRUE);
	m_CMFC_points.EnableOtherButton(_T("Доп. цвета"), FALSE, TRUE);
	m_CMFC_points.SetColor(m_CMFCPointColor);
	m_CMFC_lines.SetColor(m_CMFCLineColor);
}


BEGIN_MESSAGE_MAP(CSetParamDlg, CDialog)
	ON_BN_CLICKED(IDC_EXPORT, &CSetParamDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDC_IMPORT, &CSetParamDlg::OnBnClickedImport)
	ON_BN_CLICKED(IDC_MFCCOLORPOINTS, &CSetParamDlg::OnBnClickedMfccolorpoints)
	ON_BN_CLICKED(IDC_MFCCOLORLINES, &CSetParamDlg::OnBnClickedMfccolorlines)
END_MESSAGE_MAP()


// обработчики сообщений CSetParamDlg

void CSetParamDlg::OnBnClickedExport()
{
	
}

void CSetParamDlg::OnBnClickedImport()
{
	
}

void CSetParamDlg::OnBnClickedMfccolorpoints()
{
	m_CMFCPointColor = m_CMFC_points.GetColor();
	UpdateData(FALSE);
}


void CSetParamDlg::OnBnClickedMfccolorlines()
{
	m_CMFCLineColor = m_CMFC_lines.GetColor();
	UpdateData(FALSE);
}

