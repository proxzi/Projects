#pragma once
#include "CAcCtrl.h"


// ���������� ���� CVal2Dlg

class CVal2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CVal2Dlg)

public:
	CVal2Dlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CVal2Dlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VAL2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	double DiamShest2;
	double DiamPod2;
	double DiamOsnov2;
	double LongB1;
	double LongB2;
	double LongB3;
	double LongB4;
};
