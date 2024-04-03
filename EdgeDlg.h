WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once

#include "GraphInfo.h"

// EdgeDlg dialog

class EdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EdgeDlg)

public:
	EdgeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EdgeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
    virtual BOOL OnInitDialog();

private:
    void initList();


public:
    EdgeInfo edgeinfo;
    GraphInfo* graph;

private:
    CComboBox m_combo_begin;
    CComboBox m_combo_end;
};
