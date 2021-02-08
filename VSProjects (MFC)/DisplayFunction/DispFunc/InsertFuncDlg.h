#pragma once


// диалоговое окно CInsertFuncDlg

class CInsertFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertFuncDlg)

public:
	CInsertFuncDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CInsertFuncDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERTFUNCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_CInputSTR;
};
