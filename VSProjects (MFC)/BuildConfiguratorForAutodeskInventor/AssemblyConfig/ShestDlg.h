#pragma once
#include "CAcCtrl.h"


// диалоговое окно CShestDlg

class CShestDlg : public CDialog
{
	DECLARE_DYNAMIC(CShestDlg)

public:
	CShestDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CShestDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double Diam2;
	double DiamVerh2;
	double ZubVisota2;
	int Kol_vo_Zubov2;
	double DiamShest2;
	double LongB4;
};
