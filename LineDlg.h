WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "RouteInfo.h"
// LineDlg dialog

class LineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LineDlg)

public:
	LineDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LineDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedOk();

public:
    RouteInfo m_info;
};
