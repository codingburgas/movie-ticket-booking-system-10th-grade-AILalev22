// CLogSignDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CLogSignDlg.h"
//
#include "process.h"
#include "find.h"
#include "misc.h"
// 
// CLogSignDlg dialog

IMPLEMENT_DYNAMIC(CLogSignDlg, CDialog)

CLogSignDlg::CLogSignDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CLogSignDlg, pParent)
{

}

CLogSignDlg::~CLogSignDlg()
{
}

void CLogSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogSignDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLogSignDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP, &CLogSignDlg::OnBnClickedButtonSignup)
END_MESSAGE_MAP()


// CLogSignDlg message handlers
BOOL CLogSignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;

	CFont m_font; // font var to use in setfont
	_tcscpy_s(lf.lfFaceName, L"Arial");
	m_font.CreateFontIndirect(&lf);

	GetDlgItem(IDC_EDIT_EMAIL)->SetFont(&m_font); //set font for both email and password edit controls
	GetDlgItem(IDC_EDIT_PASSWORD)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLogSignDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	CString email, pass;
	GetDlgItem(IDC_EDIT_EMAIL)->GetWindowText(email);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(pass);

	bool emailEmpty = email.IsEmpty(), passEmpty = pass.IsEmpty();
	CString msg;
	if (emailEmpty && passEmpty)
	{
		msg = L"Please enter an email and a password";
	}
	else
	{
		if (emailEmpty)
			msg = L"Please enter an email";
		else if (passEmpty)
			msg = L"Please enter a password";
		else
		{
			
			if (Find::FindAccount({ Misc::ToStr(email),Misc::ToStr(pass) }))
				msg = L"Logged in successfully";
			else
				msg = L"User doesn't exist";
		}
	}
	GetDlgItem(IDC_STATIC_MSG_REGISTER)->SetWindowTextW(msg);
	
}
void CLogSignDlg::OnBnClickedButtonSignup()
{
	// TODO: Add your control notification handler code here
	//IDC_STATIC_MSG_REGISTER - empty static to color
}
/*
HBRUSH CLogSignDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->SetTextColor(RGB(255, 0, 0));

		static CBrush brush(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(255, 255, 255));

		return brush;
	}
*/