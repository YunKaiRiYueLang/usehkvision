// APIDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "APIDemo.h"
#include "APIDemoDlg.h"
#include "MyShowMsg.h"


char startpath[MAX_PATH] = { 0 };

double YUV2RGB_CONVERT_MATRIX[3][3] =
{
	{ 1, 0, 1.4022 },
	{ 1, -0.3456, -0.7145 },
	{ 1, 1.771, 0 }
};


static void ConvertYUV2RGB(byte* yuvFrame, byte* rgbFrame, int width, int height);
static void WriteBMP(byte* rgbFrame, int width, int height, const char* bmpFile);


//实时播放回调函数定义
void CALLBACK StreamCallBack(VIDEO_INT64 i64PlayHandle, int iStreamDataType, 
							const char* pDataArray, int iDataLen, void* pUserData)
{
    time_t tmp = time(NULL);
    if (tmp - g_pMainDlg->time4Stream > 1)
    {
        g_pMainDlg->time4Stream = tmp;
        CString csMsg;
        csMsg.Format("iStreamDataType is %d, iDataLen is %d", iStreamDataType, iDataLen);
        char *pMsg = new char[csMsg.GetLength() + 1];
        strcpy_s(pMsg, csMsg.GetLength() + 1, csMsg.GetBuffer());

        char* pType = "1";
        ::PostMessage(g_pMainDlg->GetSafeHwnd(), CALLBACKMSG, (WPARAM)pType, (LPARAM)pMsg);
    }
}


//YUV数据回调回调函数定义
void CALLBACK DecodedDataCallback(VIDEO_INT64 i64PlayHandle, const char* pDataArray, 
								 int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData)
{
    time_t tmp = time(NULL);
    if (tmp - g_pMainDlg->time4YUV > 1)
    {
        g_pMainDlg->time4YUV = tmp;
        CString csMsg;
        csMsg.Format("iDataLen is %d, iTimeStamp is %d", iDataLen, iTimeStamp);
        char *pMsg = new char[csMsg.GetLength() + 1];
        strcpy_s(pMsg, csMsg.GetLength() + 1, csMsg.GetBuffer());

        char* pType = "2";
        ::PostMessage(g_pMainDlg->GetSafeHwnd(), CALLBACKMSG, (WPARAM)pType, (LPARAM)pMsg);
    }
}

//消息回调回调函数定义
void CALLBACK MsgCallBack(VIDEO_INT64 i64PlayHandle, int iMsg, void* pUserData)
{

    time_t tmp = time(NULL);
    if (tmp - g_pMainDlg->time4Msg >= 1)
    {
        g_pMainDlg->time4Msg = tmp;
        CString csMsg;
        csMsg.Format("msg type is %d", iMsg);
        char *pMsg = new char[csMsg.GetLength() + 1];
        strcpy_s(pMsg, csMsg.GetLength() + 1, csMsg.GetBuffer());

        char* pType = "3";
        ::PostMessage(g_pMainDlg->GetSafeHwnd(), CALLBACKMSG, (WPARAM)pType, (LPARAM)pMsg);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAPIDemoDlg dialog


CAPIDemoDlg::CAPIDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAPIDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAPIDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_lPlayHandle[0] = -1;
	m_lPlayHandle[1] = -1;
	m_lPlayHandle[2] = -1;
	m_lPlayHandle[3] = -1;
	m_lRePlayHandleR = -1;
	m_lDownloadHandle = -1;
	m_lRePlayHandleL = -1;
    time4Stream = 0;
    time4Msg = 0;
    time4YUV = 0;
}

void CAPIDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAPIDemoDlg)
	DDX_Control(pDX, IDC_TAB_OPERATE, m_tabOperate);
	DDX_Control(pDX, IDC_EDIT_MSG, m_ctrlMsg);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CAPIDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CAPIDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_OPERATE, OnSelchangeTabOperate)
	//}}AFX_MSG_MAP
	ON_LBN_DBLCLK(IDC_LIST1, &CAPIDemoDlg::OnLbnDblclkList1)
	ON_MESSAGE(CALLBACKMSG, &CAPIDemoDlg::OnCallbackmsg)
    ON_MESSAGE(SHOWMSG, &CAPIDemoDlg::OnShowMsg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//
void CAPIDemoDlg::CreateTab()
{
	char path[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, path, MAX_PATH);

	CString tmp = path;

	int pos = tmp.ReverseFind('\\') + 1;
	tmp = tmp.Left(pos);

	memcpy(startpath, tmp.GetBuffer(), tmp.GetLength());

	m_tabOperate.InsertItem(0, "初始化及登录");
	m_tabOperate.InsertItem(1, "视频预览");
	m_tabOperate.InsertItem(2, "远程录像");
	//m_tabOperate.InsertItem(4, "本地录像");

	m_dlgInit.Create(IDD_DLG_SUB_INIT, &m_tabOperate);
	m_dlgReal.Create(IDD_DLG_SUB_REAL, &m_tabOperate);
	m_dlgRemoteRec.Create(IDD_DLG_SUB_REMOTEREC, &m_tabOperate);
	//m_dlgLocalRec.Create(IDD_DLG_SUB_LOCALREC, &m_tabOperate);

	CRect tabRect;
	m_tabOperate.GetClientRect(&tabRect);

	tabRect.top += 20;
	tabRect.bottom -= 5;
	tabRect.left += 5;
	tabRect.right -= 5;

	m_dlgInit.MoveWindow(tabRect);
	m_dlgReal.MoveWindow(tabRect);
	m_dlgRemoteRec.MoveWindow(tabRect);
	//m_dlgLocalRec.MoveWindow(tabRect);

	m_dlgInit.ShowWindow(SW_SHOW);
	m_dlgReal.ShowWindow(SW_HIDE);
	m_dlgRemoteRec.ShowWindow(SW_HIDE);
	//m_dlgLocalRec.ShowWindow(SW_HIDE);

	m_tabOperate.SetCurSel(0);

}

void CAPIDemoDlg::ShowMsg(CString csMsg)
{
    /*std::string* pszBuf = new std::string(csMsg.GetBuffer(0));
    *pszBuf = csMsg.GetBuffer();
    this->PostMessage(SHOWMSG, pszBuf);*/
    int cnt = m_listbox.GetCount();
    if ( cnt >= 100 )
    {
        m_listbox.ResetContent();
    }

    m_listbox.InsertString(cnt, csMsg);
    m_listbox.SetCurSel(cnt);
}



void CAPIDemoDlg::PrintCallMsg(char* csFunc, long lVal)
{
	CString msg;

	switch ( lVal )
	{
	case -1:	msg = "调用失败";							break;
	case 0:		msg = "调用成功";							break;
	case 1:		msg = "参数错误";							break;
	case 2:		msg = "空指针";								break;
	case 3:		msg = "未初始化";							break;
	case 4:		msg = "句柄无效";							break;
	case 5:		msg = "创建实例失败";						break;
	case 6:		msg = "申请内存失败";						break;
	case 7:		msg = "网络异常";							break;
	case 8:		msg = "不支持";								break;
	case 9:		msg = "回调设置失败";						break;
	case 10:	msg = "取流异常";							break;
	case 11:	msg = "停止取流异常";						break;
	case 12:	msg = "解码异常";							break;
	case 13:	msg = "停止解码异常";						break;
	case 14:	msg = "时间戳无效";							break;
	case 15:	msg = "声音相关错误";						break;
	case 16:	msg = "抓拍失败";							break;
	case 17:	msg = "查询播放时间戳失败";				break;
	case 18:	msg = "内部错误";							break;
	case 19:	msg = "播放控制失败";						break;
    case 20:    msg = "调用次序不对";                      break;
	default:	msg = "其它错误";							break;
	}

	CString csMsg;
	csMsg.Format("%s : %s", csFunc, msg);

	ShowMsg(csMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CAPIDemoDlg message handlers

BOOL CAPIDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if ( pSysMenu != NULL )
	//{
	//	CString strAboutMenu;
	//	strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	if ( !strAboutMenu.IsEmpty() )
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}

	//}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	IsSaveBmp = FALSE;
	// TODO: Add extra initialization here
	g_pMainDlg = this;

	CreateTab();

    SetTimer(0, 1000, NULL);   // 定时器，防止回调播放消息、码流、YUV数据时展示数据导致主线程卡死

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CAPIDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAPIDemoDlg::OnPaint()
{
	if ( IsIconic() )
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAPIDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

//
void CAPIDemoDlg::OnSelchangeTabOperate(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nTab = m_tabOperate.GetCurSel();

	switch ( nTab )
	{
	case 0:
	m_dlgInit.ShowWindow(SW_SHOW);
	m_dlgReal.ShowWindow(SW_HIDE);
	m_dlgRemoteRec.ShowWindow(SW_HIDE);
	//m_dlgLocalRec.ShowWindow(SW_HIDE);
	break;
	case 1:
	m_dlgInit.ShowWindow(SW_HIDE);
	m_dlgReal.ShowWindow(SW_SHOW);
	m_dlgRemoteRec.ShowWindow(SW_HIDE);
	//m_dlgLocalRec.ShowWindow(SW_HIDE);
	break;
	case 2:
	m_dlgInit.ShowWindow(SW_HIDE);
	m_dlgReal.ShowWindow(SW_HIDE);
	m_dlgRemoteRec.ShowWindow(SW_SHOW);
	//m_dlgLocalRec.ShowWindow(SW_HIDE);
	break;
	default:
	m_dlgInit.ShowWindow(SW_SHOW);
	m_dlgReal.ShowWindow(SW_HIDE);
	m_dlgRemoteRec.ShowWindow(SW_HIDE);
	//m_dlgLocalRec.ShowWindow(SW_HIDE);
	break;
	}//switch

	*pResult = 0;
}



string AnsiToUtf8(LPCSTR Ansi)
{
	int WLength = MultiByteToWideChar(CP_ACP, 0, Ansi, -1, NULL, 0);
	LPWSTR pszW = (LPWSTR)_alloca((WLength + 1) * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, Ansi, -1, pszW, WLength);

	int ALength = WideCharToMultiByte(CP_UTF8, 0, pszW, -1, NULL, 0, NULL, NULL);
	LPSTR pszA = (LPSTR)_alloca(ALength + 1);
	WideCharToMultiByte(CP_UTF8, 0, pszW, -1, pszA, ALength, NULL, NULL);
	pszA[ALength] = '\0';

	string retStr(pszA);

	return retStr;
}

string WcharToUtf8(LPCWSTR szUnicode)
{
	int ALength = WideCharToMultiByte(CP_UTF8, 0, szUnicode, -1, NULL, 0, NULL, NULL);
	LPSTR pszA = (LPSTR)_alloca(ALength + 1);
	WideCharToMultiByte(CP_UTF8, 0, szUnicode, -1, pszA, ALength, NULL, NULL);
	pszA[ALength] = '\0';

	string retStr(pszA);
	return retStr;
}

string Utf8toAnsi(LPCSTR utf8)
{
	int WLength = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, NULL);
	LPWSTR pszW = (LPWSTR)_alloca((WLength + 1) * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, pszW, WLength);
	pszW[WLength] = '\0';

	int ALength = WideCharToMultiByte(CP_ACP, 0, pszW, -1, NULL, 0, NULL, NULL);
	LPSTR pszA = (LPSTR)_alloca(ALength + 1);
	WideCharToMultiByte(CP_ACP, 0, pszW, -1, pszA, ALength, NULL, NULL);
	pszA[ALength] = '\0';

	string retStr = pszA;

	return retStr;

	//return pszA;
}

LPCWSTR Utf8toWchar(LPCSTR utf8)
{
	int WLength = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, NULL);
	LPWSTR pszW = (LPWSTR)_alloca((WLength + 1) *sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, pszW, WLength);
	pszW[WLength] = '\0';
	return pszW;
}




void CAPIDemoDlg::OnLbnDblclkList1()
{
	// TODO:  在此添加控件通知处理程序代码

	int index = m_listbox.GetCurSel();
	if ( index == -1 )
	{
		return;
	}

	CString msg;
	m_listbox.GetText(index, msg);

	CMyShowMsg myshow(msg.GetBuffer());
	myshow.DoModal();

}


afx_msg LRESULT CAPIDemoDlg::OnCallbackmsg(WPARAM wParam, LPARAM lParam)
{
	CString msg;

	char *n = (char*)wParam;
	char *a = (char*)lParam;

	msg.Format("%s\n", a);

	//char *b = NULL;
	//a = (char*)b;

	if ( a != NULL )
	{
		delete[]a;
	}
	int switch_on = 0;
	if ( n != NULL )
	{
		switch_on = atoi(n);
	}


	switch ( switch_on )
	{
	case 1:
	::SetDlgItemText(g_pMainDlg->GetSafeHwnd(), IDC_STATIC_MSG, "StreamCallBack");
	break;

	case 2:
	::SetDlgItemText(g_pMainDlg->GetSafeHwnd(), IDC_STATIC_MSG, "DecodedDataCallback");
	break;

	case 3:
	::SetDlgItemText(g_pMainDlg->GetSafeHwnd(), IDC_STATIC_MSG, "MsgCallBack");
	break;

	default:
	break;
	}

	//AfxMessageBox(msg);

	::SetDlgItemText(g_pMainDlg->GetSafeHwnd(), IDC_STATIC_MSG, msg.GetBuffer());

	return 0;
}

LRESULT CAPIDemoDlg::OnShowMsg( WPARAM wparam, LPARAM lparam )
{
    return 0;
}

void CAPIDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//Video_Fini();

	CDialog::OnClose();
}
