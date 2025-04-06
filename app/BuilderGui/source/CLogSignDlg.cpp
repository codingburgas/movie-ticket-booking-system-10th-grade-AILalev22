// CLogSignDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CLogSignDlg.h"
//

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

	MySQL::Init("tcp://127.0.0.1:3306", "root", "root1234!!??"); // init database manager
	MySQL::GetSQL()->SetDB("dataticket");// set db

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLogSignDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	CString email, pass;
	GetDlgItem(IDC_EDIT_EMAIL)->GetWindowText(email);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(pass);

	bool email_empty = email.IsEmpty(), pass_empty = pass.IsEmpty();
	CString msg;
	if (email_empty && pass_empty)
	{
		msg = L"Please enter an email and a password";
	}
	else
	{
		if (email_empty)
			msg = L"Please enter an email";
		else if (pass_empty)
			msg = L"Please enter a password";
		else
		{
			switch (Auth::LogUser({ Misc::ToStr(email),Misc::ToStr(pass) }))
			{
			case Error::SUCCESSFUL: msg = L"Logged in successfully."; break;
			case Error::ERROR_EXISTS: msg = L"User doesn't exist."; break;
			case Error::ERROR_INPUT: msg = L"Wrong password. Try again later."; break;
			default: msg = L"Unexpected error"; break;
			}				
		}
	}
	GetDlgItem(IDC_STATIC_MSG_REGISTER)->SetWindowTextW(msg);
	
}
void CLogSignDlg::OnBnClickedButtonSignup()
{
	// TODO: Add your control notification handler code here
	//IDC_STATIC_MSG_REGISTER - empty static to color
	CString email, pass;
	GetDlgItem(IDC_EDIT_EMAIL)->GetWindowText(email);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(pass);

	bool email_empty = email.IsEmpty(), pass_empty = pass.IsEmpty();
	CString msg;
	if (email_empty && pass_empty)
	{
		msg = L"Please enter an email and a password";
	}
	else
	{
		if (email_empty)
			msg = L"Please enter an email";
		else if (pass_empty)
			msg = L"Please enter a password";
		else
		{
			switch (Auth::SignUser({ Misc::ToStr(email),Misc::ToStr(pass) }))
			{
			case Error::SUCCESSFUL: msg = L"Signed up successfully."; break;
			case Error::ERROR_DATABASE: msg = L"Internal error. Please try again later."; break;
			case Error::ERROR_EXISTS: msg = L"User already exists. Please try again later."; break;
			case Error::ERROR_INPUT: msg = L"Please user password and email that are:\natleast 8 characters long\nhave big and small leters\nhave numbers"; break;
			default: msg = L"Unexpected error.Please try again later"; break;			
			}
		}
	}
	GetDlgItem(IDC_STATIC_MSG_REGISTER)->SetWindowTextW(msg);
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