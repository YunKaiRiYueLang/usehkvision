// APIDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "APIDemo.h"
#include "APIDemoDlg.h"


CAPIDemoDlg * g_pMainDlg = NULL;
//CSubDlgLocalRec * g_SubDlg = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAPIDemoApp

BEGIN_MESSAGE_MAP(CAPIDemoApp, CWinApp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAPIDemoApp construction

CAPIDemoApp::CAPIDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAPIDemoApp object

CAPIDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAPIDemoApp initialization

BOOL CAPIDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	CAPIDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
