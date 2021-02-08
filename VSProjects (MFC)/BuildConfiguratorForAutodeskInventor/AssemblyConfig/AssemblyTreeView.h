#include  "Val1Dlg.h"
#include  "Val2Dlg.h"
#include "Pod1Dlg.h"
#include "Pod2Dlg.h"
#include "KolDlg.h"
#include "ShestDlg.h"

#pragma once

// представление CAssemblyTreeView

class CAssemblyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CAssemblyTreeView)

protected:

	CAssemblyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CAssemblyTreeView();

public:
	HTREEITEM m_hRoot;
	void Code();
	/*
	HTREEITEM m_hComponent1;
	HTREEITEM m_hComponent2;
	HTREEITEM m_hComponent3;*/

	//CArray <HTREEITEM, HTREEITEM> m_Items;

	int m_iSelected = -1;
	CStringArray m_ComponentNames;
	
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	void CAssemblyTreeView::FillTree();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int VvodParametrov = 0;
	bool val1 = false;
	bool val2 = false;
	bool pod1 = false;
	bool pod2 = false;
	bool shest = false;
	bool kol = false;
public:
	//Временные переменные
	double DiamPod = 8;//Диаметр подшипника
	double DiamOsnov = 12;//Диаметр основания
	double DiamShest = 10;//Диаметр шестеренки
	double Long1 = 4;//Ширина подшипник
	double Long2 = 10;//Ширина колеса
	double Long3 = 12;//Ширина основания

	double DiamShest2 = 5;//Диаметр шестеренки
	double DiamPod2 = 14;//Диаметр подшипника
	double DiamOsnov2 = 16;//Диаметр основания
	double LongB1 = 8;//Ширина участка под подшипник
	double LongB2 = 20;//Ширина основания
	double LongB3 = 5;//Ширина подшипника
	double LongB4 = 8;//Ширина шестерёнки

	double DiamVnesh = 16;
	int Kol_Vo_Shar = 12;
	double DiamShar = 3;

	double DiamVnesh2 = 25;
	int Kol_Vo_Shar2 = 12;
	double DiamShar2 = 3;

	double Diam = 45;
	double DiamVerh = 30;
	double ZubVisota = 2;
	int Kol_vo_Zubov = 26;

	double Diam2 = 20;
	double DiamVerh2 = 16;
	double ZubVisota2 = ZubVisota;
	int Kol_vo_Zubov2 = 16;



	CVal1Dlg Val01;
	CVal2Dlg Val02;
	CPod1Dlg Pod01;
	CPod2Dlg Pod02;
	CShestDlg Shest;
	CKolDlg Kol;

};


