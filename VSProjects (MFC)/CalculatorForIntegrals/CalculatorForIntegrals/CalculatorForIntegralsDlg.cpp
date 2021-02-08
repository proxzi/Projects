#include "stdafx.h"
#include "CalculatorForIntegrals.h"
#include "CalculatorForIntegralsDlg.h"
#include "afxdialogex.h"
#include "Parser.h"
#include <string>
#include <atlstr.h>
#include <algorithm> 

#define PI 4.0*atan(1.0)

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CCalculatorForIntegralsDlg::CCalculatorForIntegralsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATORFORINTEGRALS_DIALOG, pParent)
	, m_dEnterA(0)
	, m_dEnterB(1)
	, m_dShowA(0)
	, m_dShowB(1)
	, IntegrStrExpr(_T("sqrt(x)"))
	, m_iChose(0)
	, m_dStep(0)
	, m_dSolution(0)
	, m_iEps(3)
	, m_bchose(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorForIntegralsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_dEnterA);
	DDX_Text(pDX, IDC_EDIT3, m_dEnterB);
	DDX_Text(pDX, IDC_EDIT5, m_dShowA);
	DDX_Text(pDX, IDC_EDIT4, m_dShowB);
	DDX_Text(pDX, IDC_EDIT1, IntegrStrExpr);
	DDX_Text(pDX, IDC_EDIT7, m_dSolution);
	DDX_Text(pDX, IDC_EDIT8, m_iEps);
	DDX_Check(pDX, IDC_CHECK1, m_bchose);
	DDX_Control(pDX, IDC_STATIC1, m1);
	DDX_Control(pDX, IDC_STATIC2, m2);
	DDX_Control(pDX, IDC_EDIT4, m3);
	DDX_Control(pDX, IDC_EDIT5, m4);
	DDX_Control(pDX, IDC_EDIT2, m5);
	DDX_Control(pDX, IDC_EDIT3, m6);
	DDX_Control(pDX, IDC_STATIC3, m7);
	DDX_Control(pDX, IDC_STATIC4, m8);
	DDX_Control(pDX, IDC_STATIC5, m9);
	DDX_Control(pDX, IDC_RADIO1, m10);
	DDX_Control(pDX, IDC_RADIO4, m11);
	DDX_Control(pDX, IDC_RADIO2, m12);
	DDX_Control(pDX, IDC_RADIO3, m13);
	DDX_Control(pDX, IDC_RADIO5, m14);
}

BEGIN_MESSAGE_MAP(CCalculatorForIntegralsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorForIntegralsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CCalculatorForIntegralsDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CCalculatorForIntegralsDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CCalculatorForIntegralsDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_CHECK1, &CCalculatorForIntegralsDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO4, &CCalculatorForIntegralsDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CCalculatorForIntegralsDlg::OnBnClickedRadio5)
END_MESSAGE_MAP()

BOOL CCalculatorForIntegralsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	m11.ShowWindow(SW_HIDE);
	m14.ShowWindow(SW_HIDE);
	CButton* pButton1 = (CButton*)GetDlgItem(IDC_RADIO1);
	pButton1->SetCheck(m_iChose == 0);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCalculatorForIntegralsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CCalculatorForIntegralsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCalculatorForIntegralsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorForIntegralsDlg::OnBnClickedButton1()
{
	UpdateData();
	m_dStep = pow(10, -m_iEps);
	m_dShowA = m_dEnterA;
	m_dShowB = m_dEnterB;
	m_dSolution = 0;

	if (m_iChose == 0)
		Parabola();
	else if (m_iChose == 1)
		Trapeze();
	else if (m_iChose == 2)
		Rectangle();
	else if (m_iChose == 3)
		Dichotomy();
	else
		Newton();

	UpdateData(FALSE);
}
double CCalculatorForIntegralsDlg::Fonct(CString Cstr,double x) {

	try {
		Parser p(Cstr,x);
		return p.eval(p.parse());
	}
	catch (std::exception& e) {
		//MessageBox(L"Некорректный ввод выражения", L"Предупреждение", MB_OK | MB_ICONWARNING);
		return 0;
	}
}
char * CCalculatorForIntegralsDlg::ReplaceXbyNumber(CString Cstr,char sym, double x)
{
	if (Cstr.Find(sym) == -1)
	{
		
		strcpy_s(buff, CT2A(Cstr));
		return buff;
	}
	CString TemplSTR = Cstr;
	CString TemplSTR2 = NULL;
	CString TemplSTR3 = NULL;
	TemplSTR2.Format(_T("%f"), x);
	int PlaceOfXVar = 0;
	int XVar = 0;
	for (int i = 0; i < TemplSTR.GetLength(); i++)
	{
		XVar = TemplSTR.Find(sym, PlaceOfXVar);
		PlaceOfXVar = XVar;
		TemplSTR3 = TemplSTR.Left(XVar);
		TemplSTR3 += TemplSTR2;
		TemplSTR3 += TemplSTR.Right(TemplSTR.GetLength() - XVar - 1);
		TemplSTR = TemplSTR3;
		if (XVar != -1)
			i = XVar;
		if (TemplSTR.Find(sym) == -1)
			break;
	}
	strcpy_s(buff, CT2A(TemplSTR3));
	
	return buff;
}

void CCalculatorForIntegralsDlg::Rectangle()
{
	int sign = 1;
	if (m_dEnterA > m_dEnterB)
	{
		swap(m_dEnterA, m_dEnterB);
		sign = -1;
	}
	for (double start = m_dEnterA; start < m_dEnterB; start += m_dStep)
		m_dSolution += Fonct(IntegrStrExpr,start) * m_dStep;
	m_dSolution *= sign;
	if (sign == -1)
		swap(m_dEnterA, m_dEnterB);
}

void CCalculatorForIntegralsDlg::Trapeze()
{
	int sign = 1;
	if (m_dEnterA > m_dEnterB)
	{
		swap(m_dEnterA, m_dEnterB);
		sign = -1;
	}
	for (double start = m_dEnterA; start < m_dEnterB; start += m_dStep)
		m_dSolution += ((Fonct(IntegrStrExpr, start) + Fonct(IntegrStrExpr,start + m_dStep)) / 2)*m_dStep;
	m_dSolution *= sign;
	if (sign == -1)
		swap(m_dEnterA, m_dEnterB);
}

double CCalculatorForIntegralsDlg::Diff(double x)
{
	return (Fonct(IntegrStrExpr, x+0.0001) - Fonct(IntegrStrExpr, 0.0001)) / 0.0001;
}

double CCalculatorForIntegralsDlg::SecondDiff(double x)
{
	return (Diff(x + 0.0001) - Diff(x)) / 0.0001;
}


void CCalculatorForIntegralsDlg::Newton()
{
	double A = 0, C = 0, B = A + m_dStep;
	while (Fonct(IntegrStrExpr, A) *Fonct(IntegrStrExpr, B)  > 0)
	{
		A += m_dStep;
		B += m_dStep;
	}
	C = (A + B) / 2;
	while (abs(A - B) > m_dStep)
	{
		if (Fonct(IntegrStrExpr, A) *Fonct(IntegrStrExpr, C)  < 0)
			B = C;
		else
			A = C;
		if (B - A > m_dStep)
			C = (A + B) / 2;
	}

	m_dSolution = C;
}
void CCalculatorForIntegralsDlg::Dichotomy()
{
	double A = 0, C = 0, B = A + m_dStep, An, An1;
	while (Fonct(IntegrStrExpr, A) *Fonct(IntegrStrExpr, B)  > 0)
	{
		A += m_dStep;
		B += m_dStep;
	}
	if (Fonct(IntegrStrExpr, A)*SecondDiff(A) > 0)
		An = A;
	else
		An = B;
	An1 = An + m_dStep;
	while (abs(An1 - An) > m_dStep)
	{
		An1 = An - Fonct(IntegrStrExpr, An) / Diff(An);
	}

	m_dSolution = An1;
}

void CCalculatorForIntegralsDlg::Parabola()
{
	int n = 40;
	double h = (m_dEnterB - m_dEnterA) / n;
	double I2 = 0;
	double I4 = Fonct(IntegrStrExpr, m_dEnterA + h);
	for (int i = 2; i < n; i += 2)
	{
		I4 += Fonct(IntegrStrExpr,m_dEnterA + (i + 1)*h);
		I2 += Fonct(IntegrStrExpr,m_dEnterA + i*h);
	}
	m_dSolution = Fonct(IntegrStrExpr,m_dEnterA) + Fonct(IntegrStrExpr,m_dEnterB) + 4 * I4 + 2 * I2;
	m_dSolution = m_dSolution * h / 3;
}

void CCalculatorForIntegralsDlg::OnBnClickedRadio1()
{
	m_iChose = 0;
}


void CCalculatorForIntegralsDlg::OnBnClickedRadio2()
{
	m_iChose = 1;
}


void CCalculatorForIntegralsDlg::OnBnClickedRadio3()
{
	m_iChose = 2;
}


void CCalculatorForIntegralsDlg::OnBnClickedRadio4()
{
	m_iChose = 3;
}


void CCalculatorForIntegralsDlg::OnBnClickedRadio5()
{
	m_iChose = 4;
}


void CCalculatorForIntegralsDlg::AdvancedParHide()
{
	m1.ShowWindow(SW_HIDE);
	m2.ShowWindow(SW_HIDE);
	m3.ShowWindow(SW_HIDE);
	m4.ShowWindow(SW_HIDE);
	m5.ShowWindow(SW_HIDE);
	m6.ShowWindow(SW_HIDE);
	m7.ShowWindow(SW_HIDE);
	m8.ShowWindow(SW_HIDE);
	m9.ShowWindow(SW_HIDE);
	m10.ShowWindow(SW_HIDE);
	m11.ShowWindow(SW_SHOW);
	m12.ShowWindow(SW_HIDE);
	m13.ShowWindow(SW_HIDE);
	m14.ShowWindow(SW_SHOW);
	m_iChose = 3;
	CButton* pButton2 = (CButton*)GetDlgItem(IDC_RADIO4);
	pButton2->SetCheck(m_iChose == 3);

}
void CCalculatorForIntegralsDlg::AdvancedParShow()
{
	m1.ShowWindow(SW_SHOW);
	m2.ShowWindow(SW_SHOW);
	m3.ShowWindow(SW_SHOW);
	m4.ShowWindow(SW_SHOW);
	m5.ShowWindow(SW_SHOW);
	m6.ShowWindow(SW_SHOW);
	m7.ShowWindow(SW_SHOW);
	m8.ShowWindow(SW_SHOW);
	m9.ShowWindow(SW_SHOW);
	m10.ShowWindow(SW_SHOW);
	m11.ShowWindow(SW_HIDE);
	m12.ShowWindow(SW_SHOW);
	m13.ShowWindow(SW_SHOW);
	m14.ShowWindow(SW_HIDE);
	m_iChose = 0;
}

void CCalculatorForIntegralsDlg::OnBnClickedCheck1()
{
	if (!m_bchose) {
		AdvancedParHide();
		m_bchose = true;
	}
	else {
		AdvancedParShow();
		m_bchose = false;
	}
}

