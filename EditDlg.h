WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once


// EditDlg dialog
#include "Canvas.h"
#include "NavigationEngine.h"

class EditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditDlg)

public:
	EditDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_DIALOG };
#endif

protected:
    HICON m_hIcon;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnPaint();
    afx_msg void OnBnClickedButtonVertexAdd();
    afx_msg void OnBnClickedButtonVertexRemove();
    afx_msg void OnBnClickedButtonEdgeAdd();
    afx_msg void OnBnClickedButtonEdgeRemove();
    afx_msg void OnSave();
    afx_msg void OnQuit();
    afx_msg void OnHelp();
    afx_msg void OnRoute();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDblclkListVertex(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListEdge(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditKeyword();
	DECLARE_MESSAGE_MAP()
private:
    virtual BOOL OnInitDialog();
    virtual void OnOK();

private:
    void initCListCtrlVertex();
    void initCListCtrlEdge();
    void updateCListCtrlVertex();
    void updateCListCtrlEdge();

private:
    Canvas m_canvas;
    NavigationEngine m_engine;
    CString m_last_name;

private:
    CListCtrl m_ctrl_list_vertex;
    CListCtrl m_ctrl_list_edge;
};
