
// DispFuncView.h : интерфейс класса CDispFuncView
//
#include "DispFuncDoc.h"
#pragma once


class CDispFuncView : public CView
{
protected: // создать только из сериализации
	CDispFuncView();
	DECLARE_DYNCREATE(CDispFuncView)

// Атрибуты
public:
	CDispFuncDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CDispFuncView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	double Numerator(int i, int k);
	double Denominator(int i);
	void LaGrange();
	int PosX(double X);
	int PosY(double Y);
	bool IsOrigParam;
};

#ifndef _DEBUG  // отладочная версия в DispFuncView.cpp
inline CDispFuncDoc* CDispFuncView::GetDocument() const
   { return reinterpret_cast<CDispFuncDoc*>(m_pDocument); }
#endif

