#pragma once
#include "CAcCtrl.h"


// диалоговое окно CKolDlg

class CKolDlg : public CDialog
{
	DECLARE_DYNAMIC(CKolDlg)

public:
	CKolDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CKolDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double Diam;
	double DiamVerh;
	double ZubVisota;
	int Kol_vo_Zubov;
	double DiamShest;//Диаметр шестеренки
	double Long2;//Ширина колеса
};
