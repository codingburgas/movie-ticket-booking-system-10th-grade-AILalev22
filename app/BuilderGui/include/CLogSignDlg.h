#pragma once
#include "afxdialogex.h"


// CLogSignDlg dialog

class CLogSignDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogSignDlg)

public:
	CLogSignDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLogSignDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLogSignDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
