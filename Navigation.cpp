WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com

// Navigation.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Navigation.h"
#include "LoginDlg.h"
#include "EditDlg.h"
#include "NavigationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNavigationApp

BEGIN_MESSAGE_MAP(CNavigationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNavigationApp construction

CNavigationApp::CNavigationApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CNavigationApp object

CNavigationApp theApp;


// CNavigationApp initialization

BOOL CNavigationApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	while (true) {
		LoginDlg dlg;
		if (dlg.DoModal() == IDOK) {
			if (dlg.m_admin) {
				EditDlg dlg;
				INT_PTR nResponse = dlg.DoModal();
			} else {
				CNavigationDlg dlg;
				INT_PTR nResponse = dlg.DoModal();
			}
		} else {
			break;
		}
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

