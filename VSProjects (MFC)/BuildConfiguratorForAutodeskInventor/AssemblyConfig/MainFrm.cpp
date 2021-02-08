
// MainFrm.cpp : реализация класса CMainFrame
//

#include "stdafx.h"
#include "AssemblyConfig.h"
#include "AssemblyTreeView.h"
#include "AssemblyConfigDoc.h"
#include "AssemblyConfigView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// создание/уничтожение CMainFrame

CMainFrame::CMainFrame()
{
	// TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return -1;      // не удалось создать
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Не удалось создать строку состояния\n");
		return -1;      // не удалось создать
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Удалите эти три строки, если не собираетесь закреплять панель инструментов
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return TRUE;
}

// диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// обработчики сообщений CMainFrame



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: добавьте специализированный код или вызов базового класса
	// TODO: Add your specialized code here and/or call the base class

	// create a splitter with 1 row, 2 columns
	
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CAssemblyTreeView), CSize(150, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CAssemblyConfigView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	m_wndSplitter.SetColumnInfo(0, 200, 10);
	/*
	CRect rect;
	m_wndSplitter.GetPane(0, 1)->GetClientRect(&rect);
	*/
	//m_ctrlModelView = new CModelViewCtrl;

	//m_ctrlModelView.CreateControl(m_ctrlModelView.GetClsid(), L"Win", WS_CHILD | WS_VISIBLE | WS_BORDER, rect, m_wndSplitter.GetPane(0, 1), 0);

	//m_ctrlModelView.PutSourcePath(L"G:\\1\\RAD.dwg");

	

	/*	CGeoArmDoc *pDoc = (CGeoArmDoc *)GetActiveDocument();
	pDoc->m_pTreeView = (CTreeView *)m_wndSplitter.GetPane( 0, 0 );
	pDoc->m_pEditView = (CEditView *)m_wndSplitter2.GetPane( 1, 0 );
	*/
	
	return TRUE;

	
}
