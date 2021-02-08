#pragma once
#include "CAcCtrl.h"


// ���������� ���� CPod1Dlg

class CPod1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CPod1Dlg)

public:
	CPod1Dlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CPod1Dlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POD1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double DiamVnesh;
	int Kol_Vo_Shar;
	double DiamShar;
	double DiamPod;
	double Long1;
};
