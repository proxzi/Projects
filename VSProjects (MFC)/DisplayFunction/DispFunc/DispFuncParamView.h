#pragma once
#include "afxcolorbutton.h"
#include "afxtempl.h"



// представление формы CDispFuncParamView

class CDispFuncParamView : public CFormView
{
	DECLARE_DYNCREATE(CDispFuncParamView)

protected:
	CDispFuncParamView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CDispFuncParamView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPFUNCPARAMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double m_dSeta;
	double m_dSetb;
	double m_dSetr;
	double m_dGeta;
	double m_dGetb;
	double m_dGetr;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	COLORREF m_CPoints;
	COLORREF m_Clines;
	CMFCColorButton m_CBPoints;
	CMFCColorButton m_CBlines;
	
	CString m_CStr;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	int m_iChose;
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedMfccolorbutton3();
	virtual void OnInitialUpdate();
	int m_iSPArrayXYSize;
	CArray<double, double> m_cSPPointX;
	CArray<double, double> m_cSPPointY;
	int m_iNumberP;
	double m_dAngle;
	afx_msg void OnBnClickedRadio3();
	int m_dIStrArrSize;
	int m_ips;
	int m_ils;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
};


