#pragma once
#include "CAcCtrl.h"


// ���������� ���� CKolDlg

class CKolDlg : public CDialog
{
	DECLARE_DYNAMIC(CKolDlg)

public:
	CKolDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CKolDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double Diam;
	double DiamVerh;
	double ZubVisota;
	int Kol_vo_Zubov;
	double DiamShest;//������� ����������
	double Long2;//������ ������
};
