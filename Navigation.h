WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

// Navigation.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNavigationApp:
// See Navigation.cpp for the implementation of this class
//

class CNavigationApp : public CWinApp
{
public:
	CNavigationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CNavigationApp theApp;
