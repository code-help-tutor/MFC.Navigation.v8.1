WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

// NavigationDlg.h : header file
//

#pragma once
#include "Canvas.h"
#include "NavigationEngine.h"

#define TIMER_UPDATE 1

// CNavigationDlg dialog
class CNavigationDlg : public CDialogEx
{
// Construction
public:
	CNavigationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAVIGATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
    afx_msg void OnEdit();
    afx_msg void OnQuit();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedButtonSearch();
    afx_msg void OnBnClickedButtonRoute();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
    virtual void OnOK();

private:
    void initList();

private:
    Canvas m_canvas;
    NavigationEngine m_engine;

private:
    CComboBox m_combo_begin;
    CComboBox m_combo_end;
    CComboBox m_combo_type;
};
