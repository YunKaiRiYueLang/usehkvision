// SubDlgInit.cpp : implementation file
//

#include "stdafx.h"
#include "APIDemo.h"
#include "SubDlgInit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgInit dialog


CSubDlgInit::CSubDlgInit(CWnd* pParent /*=NULL*/)
: CDialog(CSubDlgInit::IDD, pParent)
, isInitialize(FALSE)
{
	//{{AFX_DATA_INIT(CSubDlgInit)
	//}}AFX_DATA_INIT
}


void CSubDlgInit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgInit)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgInit, CDialog)
	//{{AFX_MSG_MAP(CSubDlgInit)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_UNINIT, OnButtonUninit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgInit message handlers

BOOL CSubDlgInit::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgInit::OnButtonInit()
{
	int iRet = VIDEO_ERR_FAIL;

	iRet = Video_Init(NULL);
	if (VIDEO_ERR_SUCCESS == iRet)
	{
		isInitialize = TRUE;
	}
	else
	{
		isInitialize = FALSE;
	}

	g_pMainDlg->PrintCallMsg("Video_Init()", iRet);
}

void CSubDlgInit::OnButtonUninit()
{
	int iRet = VIDEO_ERR_FAIL;

	iRet = Video_Fini();
	if (VIDEO_ERR_SUCCESS == iRet)
	{
		isInitialize = FALSE;
	}

	g_pMainDlg->PrintCallMsg("Video_Fini()", iRet);
}