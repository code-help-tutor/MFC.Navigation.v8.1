WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
// LoginDlg.cpp : implementation file
//

#include "pch.h"
#include "Navigation.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// LoginDlg dialog

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{
    m_admin = false;
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
END_MESSAGE_MAP()


// LoginDlg message handlers


BOOL LoginDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    ((CButton*)GetDlgItem(IDC_RADIO_GUEST))->SetCheck(TRUE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void LoginDlg::OnOK() {
    if (((CButton*)GetDlgItem(IDC_RADIO_GUEST))->GetCheck()) {
        m_admin = false;
    } else {
        m_admin = true;
    }
    CDialogEx::OnOK();
}
