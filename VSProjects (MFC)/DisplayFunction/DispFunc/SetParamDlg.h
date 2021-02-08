#pragma once
#include "afxcolorbutton.h"


// ���������� ���� CSetParamDlg

class CSetParamDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetParamDlg)

public:
	CSetParamDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CSetParamDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALSETPARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CArray <double, double> m_cSPPointX;
	CArray <double, double> m_cSPPointY;
	int m_iSPArrayXYSize;
	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedImport();
	afx_msg void OnBnClickedMfccolorpoints();
	afx_msg void OnBnClickedMfccolorlines();
	CMFCColorButton m_CMFC_points;
	CMFCColorButton m_CMFC_lines;
	COLORREF m_CMFCPointColor;
	COLORREF m_CMFCLineColor;
};
