#pragma once
#include "CAcCtrl.h"


// ���������� ���� CVal1Dlg

class CVal1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CVal1Dlg)

public:
	CVal1Dlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CVal1Dlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VAL1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double DiamPod;
	double DiamOsnov;
	double DiamShest;
	double Long1;
	double Long2;
	double Long3;
	virtual BOOL OnInitDialog();
};
