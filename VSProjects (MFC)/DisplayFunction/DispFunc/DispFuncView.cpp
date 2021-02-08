
// DispFuncView.cpp : реализаци€ класса CDispFuncView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позвол€ет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "DispFunc.h"
#endif
#include <cmath>
#include "DispFuncDoc.h"
#include "DispFuncView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define RED RGB(255,0,0)
#define GRN RGB(0,255,0)
#define BLU RGB(255,0,0)
#define WHT RGB(255,255,255)
#define BLK RGB(0,0,0)

//#define ZoomX 0.05
//#define ZoomY 0.05
// CDispFuncView

IMPLEMENT_DYNCREATE(CDispFuncView, CView)

BEGIN_MESSAGE_MAP(CDispFuncView, CView)
	// —тандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// создание/уничтожение CDispFuncView

CDispFuncView::CDispFuncView()
	: IsOrigParam(false)
	
{

}

CDispFuncView::~CDispFuncView()
{
}

BOOL CDispFuncView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменени€
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CDispFuncView

void CDispFuncView::OnDraw(CDC* pDC)
{
	CDispFuncDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: добавьте здесь код отрисовки дл€ собственных данных
	RECT pRECT = { 0 };
	GetClientRect(&pRECT);
	
	if (!IsOrigParam) {
		pDoc->m_iOriginHorizontal = pRECT.right;
		pDoc->m_iOriginVertical = pRECT.bottom;
		IsOrigParam = true;
	}
	
	double Coeff;
	double One, Two;
	pDoc->Xmax > abs(pDoc->Xmin) ? One = pDoc->Xmax : One = abs(pDoc->Xmin);
	pDoc->Ymax > abs(pDoc->Ymin) ? Two = pDoc->Ymax : Two = abs(pDoc->Ymin);
	One > Two? Coeff = One : Coeff = Two;
	double ZoomX = (pRECT.right - 50) / (2 * One);
	double ZoomY = (pRECT.bottom - 50) / (2 * Two);

	ZoomX = (pRECT.right - 50) / (2 * Coeff);
	ZoomY = (pRECT.bottom - 50) / (2 * Coeff);

	HPEN RPEN = CreatePen(PS_SOLID, pDoc->m_ilsD, pDoc->m_CLineColor);
	HPEN GPEN = CreatePen(PS_SOLID, pDoc->m_ipsD, pDoc->m_CPointColor);
	HPEN BPEN = CreatePen(PS_SOLID, 1, BLU);
	HPEN BLKPEN = CreatePen(PS_SOLID, 1, BLK);

	EXTLOGPEN pINFO;
	GetObject(GPEN, sizeof(EXTLOGPEN), &pINFO);

	if (pDoc->m_iDocChose == 0) {
		SelectObject(*pDC, RPEN);
		LaGrange();
		for (int i = 0; i < pDoc->m_iLaNum - 1; i++)
		{
			pDC->MoveTo(PosX(pDoc->m_dLagrangeX[i] * ZoomX), PosY(pDoc->m_dLagrangeY[i] * ZoomY));
			pDC->LineTo(PosX(pDoc->m_dLagrangeX[i + 1] * ZoomX), PosY(pDoc->m_dLagrangeY[i + 1] * ZoomY));
		}
	}
	if (pDoc->m_iDocChose == 1) {
		SelectObject(*pDC, RPEN);
		for (int i = 0; i < pDoc->m_iNum - 1; i++)
		{
			pDC->MoveTo(PosX(pDoc->m_dPointX[i] * ZoomX), PosY(pDoc->m_dPointY[i] * ZoomY));
			pDC->LineTo(PosX(pDoc->m_dPointX[i + 1] * ZoomX), PosY(pDoc->m_dPointY[i + 1] * ZoomY));
		}
	}
	if (pDoc->m_iDocChose == 2) {
		SelectObject(*pDC, RPEN);
		for (int i = 0; i < pDoc->m_iNum; i++)
		{
			Ellipse(*pDC,
				PosX((pDoc->m_dCoordCenterX - pDoc->m_dCoordRadius)* ZoomX),
				PosY((pDoc->m_dCoordCenterY + pDoc->m_dCoordRadius)* ZoomY),
				PosX((pDoc->m_dCoordCenterX + pDoc->m_dCoordRadius)* ZoomX),
				PosY((pDoc->m_dCoordCenterY - pDoc->m_dCoordRadius)* ZoomY));
		}
	}

	SelectObject(*pDC, GPEN);

	
	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		Ellipse(*pDC,
			(PosX(pDoc->m_dPointX[i] * ZoomX) - pINFO.elpWidth),
			(PosY(pDoc->m_dPointY[i] * ZoomY) + pINFO.elpWidth),
			(PosX(pDoc->m_dPointX[i] * ZoomX) + pINFO.elpWidth),
			(PosY(pDoc->m_dPointY[i] * ZoomY) - pINFO.elpWidth));
	}


	 /*
		SelectObject(*pDC, RPEN);
	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		Ellipse(*pDC,
			PosX((pDoc->m_dCoordCenterX - pDoc->m_dCoordRadius)* (pRECT.bottom - 30) / (2 * Coeff)),
			PosY((pDoc->m_dCoordCenterY + pDoc->m_dCoordRadius)* (pRECT.bottom - 30) / (2 * Coeff)),
			PosX((pDoc->m_dCoordCenterX + pDoc->m_dCoordRadius)* (pRECT.bottom - 30) / (2 * Coeff)),
			PosY((pDoc->m_dCoordCenterY - pDoc->m_dCoordRadius)* (pRECT.bottom - 30) / (2 * Coeff)));
	}


	SelectObject(*pDC, GPEN);


	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		Ellipse(*pDC,
			(PosX(pDoc->m_dPointX[i] * (pRECT.bottom - 30) / (2 * Coeff)) - pINFO.elpWidth),
			(PosY(pDoc->m_dPointY[i] * (pRECT.bottom - 30) / (2 * Coeff)) + pINFO.elpWidth),
			(PosX(pDoc->m_dPointX[i] * (pRECT.bottom - 30) / (2 * Coeff)) + pINFO.elpWidth),
			(PosY(pDoc->m_dPointY[i] * (pRECT.bottom - 30) / (2 * Coeff)) - pINFO.elpWidth));
	}*/
	
	
	SelectObject(*pDC, BLKPEN);
	pDC->MoveTo(pRECT.right / 2, 0);
	pDC->LineTo(pRECT.right / 2, pRECT.bottom);
	pDC->MoveTo(0, pRECT.bottom / 2);
	pDC->LineTo(pRECT.right, pRECT.bottom / 2);
}


// печать CDispFuncView

BOOL CDispFuncView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CDispFuncView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CDispFuncView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// диагностика CDispFuncView

#ifdef _DEBUG
void CDispFuncView::AssertValid() const
{
	CView::AssertValid();
}

void CDispFuncView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDispFuncDoc* CDispFuncView::GetDocument() const // встроена неотлаженна€ верси€
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	return (CDispFuncDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CDispFuncView


double CDispFuncView::Numerator(int n, int j)
{
	CDispFuncDoc* pDoc = GetDocument();
	double result = 1.0;
	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		if (j != i)
			result *= (pDoc->m_dLagrangeX[n] - pDoc->m_dPointX[i]);
	}
	return result;
}


double CDispFuncView::Denominator(int j)
{
	CDispFuncDoc* pDoc = GetDocument();
	double result = 1.0;
	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		if (j != i)
			result *= (pDoc->m_dPointX[j] - pDoc->m_dPointX[i]);
	}
	return result;
}


void CDispFuncView::LaGrange()
{
	CDispFuncDoc* pDoc = GetDocument();
	double num = pDoc->FirstPoint;
	if (pDoc->m_iNum * 10 != pDoc->m_iLaNum)
	{
		pDoc->m_iLaNum = pDoc->m_iNum * 10;
		delete[] pDoc->m_dLagrangeX;
		delete[] pDoc->m_dLagrangeY;
		pDoc->m_dLagrangeX = new double[pDoc->m_iNum * 10];
		pDoc->m_dLagrangeY = new double[pDoc->m_iNum * 10];
	}
	
	for (int n = 0; n < pDoc->m_iLaNum; n++)
	{
		pDoc->m_dLagrangeX[n] = num;
		pDoc->m_dLagrangeY[n] = 0;
		for (int j = 0; j < pDoc->m_iNum; j++)
			pDoc->m_dLagrangeY[n] += pDoc->m_dPointY[j] * Numerator(n, j) / Denominator(j);
		num += pDoc->m_dLaStep;
	}
}


int CDispFuncView::PosX(double X)
{
	CDispFuncDoc* pDoc = GetDocument();
	RECT pRECT = { 0 };
	GetClientRect(&pRECT);
	return int(double(pRECT.right) / 2 + (X * pRECT.right) / (pDoc->m_iOriginHorizontal));
}


int CDispFuncView::PosY(double Y)
{
	CDispFuncDoc* pDoc = GetDocument();
	RECT pRECT = { 0 };
	GetClientRect(&pRECT);
	return int(double(pRECT.bottom) / 2 - (Y * pRECT.bottom) / (pDoc->m_iOriginVertical));
}


