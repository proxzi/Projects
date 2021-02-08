#pragma once
#include "CAcCtrl.h"


// диалоговое окно CPod1Dlg

class CPod1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CPod1Dlg)

public:
	CPod1Dlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CPod1Dlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POD1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double DiamVnesh;
	int Kol_Vo_Shar;
	double DiamShar;
	double DiamPod;
	double Long1;
};
