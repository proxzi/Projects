
// DispFuncDoc.cpp : реализация класса CDispFuncDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "DispFunc.h"
#endif

#include "DispFuncDoc.h"
#include "SetParamDlg.h"
#include "InsertFuncDlg.h"
#include "Parser.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDispFuncDoc

IMPLEMENT_DYNCREATE(CDispFuncDoc, CDocument)

BEGIN_MESSAGE_MAP(CDispFuncDoc, CDocument)
	ON_COMMAND(ID_SETPARAM, &CDispFuncDoc::OnSetparam)
	ON_COMMAND(ForInsertFunction, &CDispFuncDoc::OnForinsertfunction)
END_MESSAGE_MAP()


// создание/уничтожение CDispFuncDoc

CDispFuncDoc::CDispFuncDoc()
	:m_CInputSTRView(_T(""))
	, m_dCoordCenterX(0)
	, m_dCoordCenterY(0)
	, m_dCoordRadius(0)
	, m_ipsD(0)
	, m_ilsD(0)
{
	// TODO: добавьте код для одноразового вызова конструктора
	m_cPointX.RemoveAll();
	m_cPointY.RemoveAll();
	m_dDocStep = 1.0;
}

CDispFuncDoc::~CDispFuncDoc()
{
	delete[] m_dPointX;
	delete[] m_dPointY;
}

BOOL CDispFuncDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	m_ipsD = 3;
	m_ilsD = 1;
	srand(unsigned(time(NULL)));
	double j = FirstPoint;
	m_dPointX = new double[m_iNum];
	m_dPointY = new double[m_iNum];
	m_dLagrangeX = new double[m_iNum*10];
	m_dLagrangeY = new double[m_iNum*10];
	for (int i = 0; i < m_iNum; i++, j += m_dStep)
	{
		m_dPointX[i] = j;
		m_dPointY[i] = sin(m_dPointX[i]);
	}
	GetMinMax();
	return TRUE;
}




// сериализация CDispFuncDoc

void CDispFuncDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
		ar << m_dDocStep;
		ar << m_cPointX.GetSize();
		for (int i = 0; i < m_cPointX.GetSize(); i++)
		{
			ar << m_cPointX[i];
			ar << m_cPointY[i];
		}
	}
	else
	{
		// TODO: добавьте код загрузки
		//ar >> ver;
		//if(ver == 1) {}
		ar >> m_dDocStep;
		int size;
		ar >> size;
		for (int i = 0; i < size; i++)
		{
			ar >> m_cPointX[i];
			ar >> m_cPointY[i];
		}
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CDispFuncDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CDispFuncDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CDispFuncDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CDispFuncDoc

#ifdef _DEBUG
void CDispFuncDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDispFuncDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CDispFuncDoc


void CDispFuncDoc::OnSetparam()
{
	CSetParamDlg Dlg;
	Dlg.m_CMFCPointColor = m_CPointColor;
	Dlg.m_CMFCLineColor = m_CLineColor;

	Dlg.m_cSPPointX.SetSize(m_iNum);
	Dlg.m_cSPPointY.SetSize(m_iNum);
	for (int i = 0; i < m_iNum; i++)
	{
		Dlg.m_cSPPointX[i] = m_dPointX[i];
		Dlg.m_cSPPointY[i] = m_dPointY[i];
	}
	Dlg.m_iSPArrayXYSize = m_iNum;
	if (Dlg.DoModal() == IDOK) {
		m_CPointColor = Dlg.m_CMFCPointColor;
		m_CLineColor = Dlg.m_CMFCLineColor;
		delete[] m_dPointX;
		delete[] m_dPointY;
		m_iNum = Dlg.m_iSPArrayXYSize;
		m_dPointX = new double[m_iNum];
		m_dPointY = new double[m_iNum];
		for (int i = 0; i < m_iNum; i++)
		{
			m_dPointX[i] = Dlg.m_cSPPointX[i];
			m_dPointY[i] = Dlg.m_cSPPointY[i];
		}
	}
	GetMinMax();
	GetCircle();
	UpdateAllViews(NULL);
}

void CDispFuncDoc::OnForinsertfunction()
{

	delete[] m_dPointX;
	delete[] m_dPointY;
	m_dPointX = new double[m_iNum];
	m_dPointY = new double[m_iNum];
		double j = FirstPoint;
		for (int i = 0; i < m_iNum; i++, j += m_dStep)
		{
			m_dPointX[i] = j;
			m_dPointY[i] = Fonct(m_CInputSTRView, m_dPointX[i]);
		}
	GetMinMax();
	UpdateAllViews(NULL);;
}

double CDispFuncDoc::Fonct(CString Cstr, double x)
{
	try {
		Parser p(Cstr, x);
		auto g = p.eval(p.parse());
		double i = g;
		return g;
	}
	catch (std::exception& e) {
		//MessageBox(L"Некорректный ввод выражения", L"Предупреждение", MB_OK | MB_ICONWARNING);
		return 0;
	}
}
void CDispFuncDoc::GetMinMax()
{
	Xmax = m_dPointX[0];
	Ymax = m_dPointY[0];
	Xmin = m_dPointX[0];
	Ymin = m_dPointY[0];
	for (int i = 1; i < m_iNum; i++)
	{
		if (Xmax < m_dPointX[i]) Xmax = m_dPointX[i];
		if (Ymax < m_dPointY[i]) Ymax = m_dPointY[i];
		if (Xmin > m_dPointX[i]) Xmin = m_dPointX[i];
		if (Ymin > m_dPointY[i]) Ymin = m_dPointY[i];
	}
}
void CDispFuncDoc::GetCircle()
{
	double x0 = 0, y0 = 0;
	for (int i = 0; i < m_iNum; i++) {
		x0 += m_dPointX[i];
		y0 += m_dPointY[i];
	}	
	x0 /= m_iNum;
	y0 /= m_iNum;
	double	Rmin, Rmax,
			x0min,x0max,
			y0min,y0max,
			R, epsilon = 0.000001;
	Xmin < Ymin ? x0min = Xmin : x0min = Ymin;
	y0min = x0min;
	Rmin = 0;
	Xmax > Ymax ? x0max = Xmax : x0max = Ymax;
	y0max = x0max;
	Rmax = abs(Xmax - Xmin) / 2+0.5;
	x0 = 5000;
	y0 = 5000;
	R = abs(Rmin + Rmax) / 2;
	while (abs(x0min - x0max) > epsilon)
	{
		CalcFunR(R, x0 - epsilon, y0) < CalcFunR(R, x0 + epsilon, y0) ? x0max = x0 : x0min = x0;
		x0 = (x0min + x0max) / 2;
	}
	while (abs(y0min - y0max) > epsilon)
	{
		CalcFunR(R, x0, y0 - epsilon) < CalcFunR(R, x0, y0 + epsilon) ? y0max = y0 : y0min = y0;
		y0 = (y0min + y0max) / 2;
	}
	while (abs(Rmin - Rmax) > epsilon)
	{
		CalcFunR(R - epsilon,x0,y0) < CalcFunR(R + epsilon, x0, y0) ? Rmax = R : Rmin = R;
		R = (Rmin + Rmax) / 2;
	}
	m_dCoordCenterX = x0;
	m_dCoordCenterY = y0;
	m_dCoordRadius = R;
}
double CDispFuncDoc::CalcFunR(double r,double x,double y)
{
	double sum = 0;
	for (int i = 0; i < m_iNum; i++) {
		sum += pow(r - sqrt(pow(m_dPointY[i] - y, 2) + pow(m_dPointX[i] - x, 2)),2);
	}
	return sum;
}