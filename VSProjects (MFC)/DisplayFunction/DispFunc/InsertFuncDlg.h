#pragma once


// ���������� ���� CInsertFuncDlg

class CInsertFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertFuncDlg)

public:
	CInsertFuncDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CInsertFuncDlg();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSERTFUNCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_CInputSTR;
};
