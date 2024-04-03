WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#pragma once


// VertexDlg dialog
#include "GraphInfo.h"

class VertexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VertexDlg)

public:
	VertexDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~VertexDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERTEX_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

protected:
    virtual BOOL OnInitDialog();

public:
    VertexInfo vertexinfo;
	bool readonly;
};
