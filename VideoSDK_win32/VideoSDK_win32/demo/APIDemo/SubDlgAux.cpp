// SubDlgAux.cpp : implementation file
//

#include "stdafx.h"
#include "APIDemo.h"
#include "SubDlgAux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgAux dialog


CSubDlgAux::CSubDlgAux(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgAux::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgAux)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubDlgAux::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgAux)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgAux, CDialog)
	//{{AFX_MSG_MAP(CSubDlgAux)
	ON_BN_CLICKED(IDC_BUTTON_GETERROR, OnButtonGeterror)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgAux message handlers

BOOL CSubDlgAux::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgAux::OnButtonGeterror()
{
	//char czErrDesc[512] = { 0 };

	int iRet = -1;

	iRet = Video_GetLastError();

	CString csMsg;
	csMsg.Format("Video_GetLastError() : [%d]", iRet);

	g_pMainDlg->ShowMsg(csMsg);

	//if ( iRet >= 0 )
	//{
	//	CString csMsg;

	//	string tmp;
	//	tmp = Utf8toAnsi(czErrDesc);

	//	csMsg.Format("´íÎóÃèÊö:%s", tmp.c_str());

	//	g_pMainDlg->ShowMsg(csMsg);
	//}
}
