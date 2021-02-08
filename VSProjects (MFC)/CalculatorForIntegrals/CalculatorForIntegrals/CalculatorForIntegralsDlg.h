
// CalculatorForIntegralsDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"


// диалоговое окно CCalculatorForIntegralsDlg
class CCalculatorForIntegralsDlg : public CDialogEx
{
// Создание
public:
	CCalculatorForIntegralsDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATORFORINTEGRALS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double m_dEnterA;
	double m_dEnterB;
	double m_dShowA;
	double m_dShowB;
	char buff[1024];
	CString IntegrStrExpr;
	int m_iChose;
	double m_dStep;
	double m_dSolution;
	afx_msg void OnBnClickedButton1();
	double Fonct(CString str,double x);
	char * ReplaceXbyNumber(CString Cstr,char, double x);
	void Rectangle();
	void Trapeze();
	void Parabola();
	void Newton();
	void Dichotomy();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	char * m_buff;
	int m_iEps;
	BOOL m_bchose;
	CStatic m1;
	CStatic m2;
	CStatic m7;
	CStatic m8;
	CStatic m9;
	CEdit m3;
	CEdit m4;
	CEdit m5;
	CEdit m6;
	void AdvancedParHide();
	void AdvancedParShow();
	afx_msg void OnBnClickedCheck1();
	CButton m10;
	CButton m11;
	CButton m12;
	CButton m13;
	CButton m14;
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	double Diff(double x);
	double SecondDiff(double x);

};
