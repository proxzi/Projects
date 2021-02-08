#pragma once
#include "CAcCtrl.h"


// ���������� ���� CPod2Dlg

class CPod2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CPod2Dlg)

public:
	CPod2Dlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CPod2Dlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POD2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double DiamVnesh2;
	int Kol_Vo_Shar2;
	double DiamShar2;
	double DiamPod2;
	double LongB3;
};
