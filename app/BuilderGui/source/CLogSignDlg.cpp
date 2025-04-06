// CLogSignDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "CLogSignDlg.h"
//
//#include "process.h"
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