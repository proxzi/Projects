// DispFuncParamView.cpp: файл реализации
//

#include "stdafx.h"
#include "DispFunc.h"
#include "DispFuncParamView.h"
#include "DispFuncDoc.h"
#include<fstream>

// CDispFuncParamView

IMPLEMENT_DYNCREATE(CDispFuncParamView, CFormView)

CDispFuncParamView::CDispFuncParamView()
	: CFormView(IDD_DISPFUNCPARAMVIEW)
	, m_dSeta(5)
	, m_dSetb(4)
	, m_dSetr(3)
	, m_dGeta(0)
	, m_dGetb(0)
	, m_dGetr(0)
	, m_CStr(_T(""))
	, m_iChose(-1)
	, m_iSPArrayXYSize(0)
	, m_iNumberP(37)
	, m_dAngle(10)
	, m_dIStrArrSize(30)
	, m_ips(3)
	, m_ils(1)
{

}

CDispFuncParamView::~CDispFuncParamView()
{
}

void CDispFuncParamView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_dSeta);
	DDX_Text(pDX, IDC_EDIT3, m_dSetb);
	DDX_Text(pDX, IDC_EDIT4, m_dSetr);
	DDX_Text(pDX, IDC_EDIT5, m_dGeta);
	DDX_Text(pDX, IDC_EDIT6, m_dGetb);
	DDX_Text(pDX, IDC_EDIT7, m_dGetr);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON2, m_CPoints);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_CBPoints);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_CBlines);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON3, m_Clines);
	DDX_Text(pDX, IDC_EDIT1, m_CStr);
	DDX_Text(pDX, IDC_EDIT8, m_iNumberP);
	DDX_Text(pDX, IDC_EDIT9, m_dAngle);
	DDX_Text(pDX, IDC_EDIT10, m_dIStrArrSize);
	DDX_Text(pDX, IDC_EDIT11, m_ips);
	DDX_Text(pDX, IDC_EDIT12, m_ils);
}

BEGIN_MESSAGE_MAP(CDispFuncParamView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CDispFuncParamView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CDispFuncParamView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDispFuncParamView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDispFuncParamView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CDispFuncParamView::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDispFuncParamView::OnBnClickedRadio2)
		ON_BN_CLICKED(IDC_RADIO3, &CDispFuncParamView::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CDispFuncParamView::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CDispFuncParamView::OnBnClickedMfccolorbutton3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDispFuncParamView::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CDispFuncParamView::OnDeltaposSpin2)
END_MESSAGE_MAP()


// диагностика CDispFuncParamView

#ifdef _DEBUG
void CDispFuncParamView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDispFuncParamView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CDispFuncParamView

//Gen
void CDispFuncParamView::OnBnClickedButton4()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CArray <double, double> m_x;
	CArray <double, double> m_y;
	srand(time(NULL));
	UpdateData();
	for (int i = 0,angle = 0; i < m_iNumberP; i++,angle+= m_dAngle)
	{
		m_x.Add(m_dSeta + m_dSetr*cos(angle) + (rand() % 200 - 100) / 1000);
		m_y.Add(m_dSetb + m_dSetr*sin(angle) + (rand() % 200 - 100) / 1000);
	}
	delete[] pDoc->m_dPointX;
	delete[] pDoc->m_dPointY;
	pDoc->m_iNum = m_iNumberP;
	pDoc->m_dPointX = new double[pDoc->m_iNum];
	pDoc->m_dPointY = new double[pDoc->m_iNum];
	for (int i = 0; i < pDoc->m_iNum; i++)
	{
		pDoc->m_dPointX[i] = m_x[i];
		pDoc->m_dPointY[i] = m_y[i];
	}
	pDoc->GetMinMax();
	pDoc->GetCircle();
	m_dGeta = pDoc->m_dCoordCenterX;
	m_dGetb = pDoc->m_dCoordCenterY;
	m_dGetr = pDoc->m_dCoordRadius;
	pDoc->m_iDocChose = -1;
	UpdateData(FALSE);
	pDoc->m_iDocChose = 2;
	pDoc->UpdateAllViews(NULL);
}

//Export
void CDispFuncParamView::OnBnClickedButton3()
{
	CFileDialog fileDialog(FALSE, _T("dat"), _T("F_Configuration"), NULL, _T("Data (*.dat) |*.dat|All Files(*.*) | *.* ||"));
	if (fileDialog.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		std::ofstream fout(fileDialog.GetPathName());
		m_iSPArrayXYSize = m_cSPPointX.GetSize();
		fout << m_CPoints << " ";
		fout << m_Clines << std::endl;
		for (int i = 0; i < m_iSPArrayXYSize; i++) {
			fout << m_cSPPointX[i] << " ";
			fout << m_cSPPointY[i] << " ";
		}
		fout.close();
		//AfxMessageBox(_T("Файл успешно сохранен.\nПуть файла ") + fileDialog.GetPathName(), MB_ICONINFORMATION | MB_OK);
	}
}

//Import
void CDispFuncParamView::OnBnClickedButton2()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	CFileDialog fileDialog(TRUE, _T("dat"), _T("F_Configuration"), NULL, _T("Data (*.dat) |*.dat|All Files(*.*) | *.* ||"));
	if (fileDialog.DoModal() == IDOK)
	{
		FILE *fl;
		_tfopen_s(&fl, fileDialog.GetPathName(), _T("rt"));
		//if (!fl) { exit(1); }
		char str[100];
		float x, y;
		CArray <double, double> m_fx;
		CArray <double, double> m_fy;
		while (fgets(str, 100, fl) != NULL) {
			if (sscanf_s(str, "%f %f", &x, &y) == 2) {
				m_fx.Add(x);
				m_fy.Add(y);
			}
		}
		m_cSPPointX.Copy(m_fx);
		m_cSPPointY.Copy(m_fy);
		m_iSPArrayXYSize = m_cSPPointX.GetSize();
		fclose(fl);

		/*
		std::ifstream fin(fileDialog.GetPathName());
		fin >> m_CMFCPointColor >> m_CMFCLineColor;
		m_cSPPointX.RemoveAll();
		m_cSPPointY.RemoveAll();
		int i = 0;
		while (fin)
		{
		m_cSPPointX.Add(0);
		m_cSPPointY.Add(0);
		fin >> m_cSPPointX[i];
		fin >> m_cSPPointY[i];
		i++;
		}
		fin.close();
		m_iSPArrayXYSize = m_cSPPointX.GetSize();
		//AfxMessageBox(_T("Файл успешно загружен.\nПуть файла ") + fileDialog.GetPathName(), MB_ICONINFORMATION | MB_OK);*/
		//m_CMFC_points.SetColor(m_CMFCPointColor);
		//m_CMFC_lines.SetColor(m_CMFCLineColor);
		UpdateData(FALSE);
		delete[] pDoc->m_dPointX;
		delete[] pDoc->m_dPointY;
		pDoc->m_iNum = m_iSPArrayXYSize;
		pDoc->m_dPointX = new double[pDoc->m_iNum];
		pDoc->m_dPointY = new double[pDoc->m_iNum];
		for (int i = 0; i < pDoc->m_iNum; i++)
		{
			pDoc->m_dPointX[i] = m_cSPPointX[i];
			pDoc->m_dPointY[i] = m_cSPPointY[i];
		}
		pDoc->GetMinMax();
		pDoc->GetCircle();
		pDoc->m_iDocChose = -1;
		pDoc->UpdateAllViews(NULL);
		pDoc->m_iDocChose = 2;
	}
	
	
}

//Set
void CDispFuncParamView::OnBnClickedButton1()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	UpdateData();
	pDoc->m_iNum = m_dIStrArrSize;
	pDoc->m_iDocChose = m_iChose;
	pDoc->m_CInputSTRView = m_CStr;
	pDoc->OnForinsertfunction();
}
void CDispFuncParamView::OnBnClickedRadio1()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_iChose = 0;
	pDoc->m_iDocChose = m_iChose;
	pDoc->UpdateAllViews(NULL);
}
void CDispFuncParamView::OnBnClickedRadio2()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_iChose = 1;
	pDoc->m_iDocChose = m_iChose;
	pDoc->UpdateAllViews(NULL);
}
void CDispFuncParamView::OnBnClickedRadio3()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_iChose = -1;
	pDoc->m_iDocChose = m_iChose;
	pDoc->UpdateAllViews(NULL);
}

void CDispFuncParamView::OnBnClickedMfccolorbutton2()
{
	m_CPoints = m_CBPoints.GetColor();
	UpdateData(FALSE);
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->m_CPointColor = m_CPoints;
	pDoc->UpdateAllViews(NULL);
}

void CDispFuncParamView::OnBnClickedMfccolorbutton3()
{
	m_Clines = m_CBlines.GetColor();
	UpdateData(FALSE);
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->m_CLineColor = m_Clines;
	pDoc->UpdateAllViews(NULL);
}

void CDispFuncParamView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	COLORREF m_CPoints = RGB(0, 255, 0);
	COLORREF m_Clines = RGB(255, 0, 0);
	m_CBlines.EnableOtherButton(_T("Доп. цвета"), FALSE, TRUE);
	m_CBPoints.EnableOtherButton(_T("Доп. цвета"), FALSE, TRUE);
	m_CBPoints.SetColor(m_CPoints);
	m_CBlines.SetColor(m_Clines);
}



void CDispFuncParamView::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	UpdateData();
	pDoc->m_ipsD = m_ips;
	pDoc->UpdateAllViews(NULL);
	*pResult = 0;
}


void CDispFuncParamView::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDispFuncDoc)));
	CDispFuncDoc* pDoc = (CDispFuncDoc*)m_pDocument;
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	UpdateData();
	pDoc->m_ilsD = m_ils;
	pDoc->UpdateAllViews(NULL);
	*pResult = 0;
}
