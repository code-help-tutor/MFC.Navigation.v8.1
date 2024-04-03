WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once


// HelpDlg dialog

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~HelpDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
