WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "RouteInfo.h"

// RouteDlg dialog

class RouteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RouteDlg)

public:
	RouteDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RouteDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROUTE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    virtual void OnOK();

public:
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonRemove();
    afx_msg void OnEnChangeEditWord();

private:
    void initCListCtrl();
    void updateCListCtrl();

public:
    bool m_modify;

private:
    CListCtrl m_ctrl_list;
    RouteInfoList m_list;
};
