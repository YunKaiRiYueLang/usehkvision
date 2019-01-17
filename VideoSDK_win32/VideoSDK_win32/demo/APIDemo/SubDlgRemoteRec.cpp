// SubDlgRemoteRec.cpp : implementation file
//

#include "stdafx.h"
#include "APIDemo.h"
#include "SubDlgRemoteRec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgRemoteRec dialog


CSubDlgRemoteRec::CSubDlgRemoteRec(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgRemoteRec::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgRemoteRec)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iSpeedRet = 0;
}


void CSubDlgRemoteRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgRemoteRec)
	DDX_Control(pDX, IDC_STATIC_RPWND, m_wndRP);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO2, m_combox);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDatePB);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTimePB);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_EndDatePB);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndTimePB);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_StartDateDL);
	DDX_Control(pDX, IDC_DATETIMEPICKER6, m_StartTimeDL);
	DDX_Control(pDX, IDC_DATETIMEPICKER7, m_EndDateDL);
	DDX_Control(pDX, IDC_DATETIMEPICKER8, m_EndTimeDL);
}


BEGIN_MESSAGE_MAP(CSubDlgRemoteRec, CDialog)
	//{{AFX_MSG_MAP(CSubDlgRemoteRec)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PICCAPTURE2, &CSubDlgRemoteRec::OnBnClickedButtonPiccapture2)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CSubDlgRemoteRec::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, &CSubDlgRemoteRec::OnBnClickedButtonResume)
	ON_BN_CLICKED(IDC_BUTTON_PLAYBACK, &CSubDlgRemoteRec::OnBnClickedButtonPlayback)
	ON_BN_CLICKED(IDC_BUTTON_STOPPLAYB, &CSubDlgRemoteRec::OnBnClickedButtonStopplayb)
	ON_BN_CLICKED(IDC_BUTTON_GETCURRENTTIME, &CSubDlgRemoteRec::OnBnClickedButtonGetcurrenttime)
	ON_BN_CLICKED(IDC_BUTTON_LOCATEPLAY, &CSubDlgRemoteRec::OnBnClickedButtonLocateplay)
	ON_BN_CLICKED(IDC_BUTTON_STOPDL, &CSubDlgRemoteRec::OnBnClickedButtonStopdl)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CSubDlgRemoteRec::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_GETVOL, &CSubDlgRemoteRec::OnBnClickedButtonGetvol)
	ON_BN_CLICKED(IDC_BUTTON_SETVOL, &CSubDlgRemoteRec::OnBnClickedButtonSetvol)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOON2, &CSubDlgRemoteRec::OnBnClickedButtonAudioon2)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOOFF2, &CSubDlgRemoteRec::OnBnClickedButtonAudiooff2)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, &CSubDlgRemoteRec::OnBnClickedButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_RAPID, &CSubDlgRemoteRec::OnBnClickedButtonRapid)
	ON_BN_CLICKED(IDC_BUTTON_SPEEDPLAY, &CSubDlgRemoteRec::OnBnClickedButtonSpeedplay)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgRemoteRec message handlers

UINT StartBThread(LPVOID lparam)
{
	CSubDlgRemoteRec* pDlg = (CSubDlgRemoteRec*)lparam;
	pDlg->Fun_StartPlay();

	return 0;
}
UINT StopBThread(LPVOID lparam)
{
	CSubDlgRemoteRec* pDlg = (CSubDlgRemoteRec*)lparam;
	pDlg->Fun_StopPlay();

	return 0;
}
UINT SpeedPlayThread(LPVOID lparam)
{
	CSubDlgRemoteRec* pDlg = (CSubDlgRemoteRec*)lparam;
	pDlg->Fun_SpeedPlay();

	return 0;
}
UINT LocatPlayThread(LPVOID lparam)
{
	CSubDlgRemoteRec* pDlg = (CSubDlgRemoteRec*)lparam;
	pDlg->Fun_LocatPlay();

	return 0;
}
int CSubDlgRemoteRec::Fun_StartPlay()
{
	CString csFileUrl,csStartTM, csEndTM;
	GetDlgItemText(IDC_EDIT_STREAMURL, csFileUrl);

	struct tm tmStart;
	memset(&tmStart,0,sizeof(tmStart));
	struct tm tmEnd;
	memset(&tmEnd,0,sizeof(tmEnd));
	CTime ctTemp;

	m_StartDatePB.GetTime(ctTemp);
	tmStart.tm_year = ctTemp.GetYear() - 1900;
	tmStart.tm_mon  = ctTemp.GetMonth() - 1;
	tmStart.tm_mday = ctTemp.GetDay();
	m_StartTimePB.GetTime(ctTemp);
	tmStart.tm_hour = ctTemp.GetHour();
	tmStart.tm_min  = ctTemp.GetMinute();
	tmStart.tm_sec  = ctTemp.GetSecond();
	time_t llStartTime = mktime(&tmStart);

	m_EndDatePB.GetTime(ctTemp);
	tmEnd.tm_year = ctTemp.GetYear() - 1900;
	tmEnd.tm_mon  = ctTemp.GetMonth() - 1;
	tmEnd.tm_mday = ctTemp.GetDay();
	m_EndTimePB.GetTime(ctTemp);
	tmEnd.tm_hour = ctTemp.GetHour();
	tmEnd.tm_min  = ctTemp.GetMinute();
	tmEnd.tm_sec  = ctTemp.GetSecond();
	time_t llEndTime = mktime(&tmEnd);

    if (llEndTime <= llStartTime)
    {
        g_pMainDlg->ShowMsg(CString(L"播放结束时间不能小于等于开始播放时间"));
        return -1;
    }

	VIDEO_INT64 llRet = -1;
	if ( g_pMainDlg->m_lRePlayHandleR >= 0 )
	{
		Video_StopPlayback(g_pMainDlg->m_lRePlayHandleR);
	}
	USERDATA stUserData;
	stUserData.ctype = RemotePlay;
	VIDEO_PLAY_REQ stReq;
	stReq.fnStream = StreamCallBack;
	stReq.fnDecodedStream = DecodedDataCallback;
	stReq.fnMsg = MsgCallBack;
	stReq.pUserData = (void*)&stUserData;
	CButton *pBtn2 = (CButton *)GetDlgItem(IDC_CHECK1);
	if (pBtn2->GetCheck())
	{
		stReq.iHardWareDecode = 1;
	}
	else
	{
		stReq.iHardWareDecode = 0;
	}
	string url = AnsiToUtf8(csFileUrl.GetBuffer());
	CButton *pBtn1 = (CButton *)GetDlgItem(IDC_CHECK1);
	if ( pBtn1->GetCheck() )
	{
		llRet = Video_StartPlayback(url.c_str(), m_wndRP, llStartTime, llEndTime, &stReq);
	}
	else
	{
		llRet = Video_StartPlayback(url.c_str(), NULL, llStartTime, llEndTime, &stReq);
	}

	if ( llRet >= 0 )
	{
		g_pMainDlg->m_lRePlayHandleR = llRet;

	}
	
    g_pMainDlg->PrintCallMsg("Video_StartPlayback()|开始回放", Video_GetLastError());

	return 0;
}
int CSubDlgRemoteRec::Fun_StopPlay()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");

		return 0;
	}
	int iRet = -1;
	iRet = Video_StopPlayback(g_pMainDlg->m_lRePlayHandleR);

	g_pMainDlg->PrintCallMsg("Video_StopPlayback()|停止回放", Video_GetLastError());

	if ( iRet >= 0 )
	{
		g_pMainDlg->m_lRePlayHandleR = -1;
		m_wndRP.Invalidate();
	}

	return 0;
}

CString CSubDlgRemoteRec::GetModuleDir() 
{ 
	HMODULE module = GetModuleHandle(0); 
	char pFileName[MAX_PATH]; 
	GetModuleFileName(module, pFileName, MAX_PATH); 

	CString csFullPath(pFileName); 
	int nPos = csFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		return CString(""); 
	else 
		return csFullPath.Left( nPos ); 
}

BOOL CSubDlgRemoteRec::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CString csCapPath = GetModuleDir() + "\\test_pic";
	GetDlgItem(IDC_EDIT_PICPATH3)->SetWindowText(csCapPath);

	GetDlgItem(IDC_EDIT_RECORDT)->SetWindowText("C:\\test_rec.mp4");
	GetDlgItem(IDC_EDIT_MAXSIZE)->SetWindowText("");

	GetDlgItem(IDC_EDIT_SPEED)->SetWindowText("1");

	m_combox.InsertString(0, "jpg");
	m_combox.InsertString(1, "bmp");

	m_combox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgRemoteRec::OnBnClickedButtonPiccapture2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString csPic;
	GetDlgItemText(IDC_EDIT_PICPATH3, csPic);
	string strPath = csPic.GetBuffer();
	int index = m_combox.GetCurSel();
	if (index == 0)
	{
		strPath += ".jpg";
	}
	else
	{
		strPath += ".bmp";
	}
	int iRet = -1;
	iRet = Video_PlaySnap(g_pMainDlg->m_lRePlayHandleR, strPath.c_str());
	g_pMainDlg->PrintCallMsg("Video_PlaySnap()|回放抓图", Video_GetLastError());
}

void CSubDlgRemoteRec::OnBnClickedButtonPause()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");

		return;
	}

	int iRet = -1;
	iRet = Video_PlayCtrl(g_pMainDlg->m_lRePlayHandleR, 0, 0);
	g_pMainDlg->PrintCallMsg("Video_PlayCtrl()|暂停", Video_GetLastError());
	return;
}

void CSubDlgRemoteRec::OnBnClickedButtonResume()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");

		return;
	}

	int iRet = -1;
	iRet = Video_PlayCtrl(g_pMainDlg->m_lRePlayHandleR, 1, 0);
	g_pMainDlg->PrintCallMsg("Video_PlayCtrl()|恢复播放", Video_GetLastError());
	return;
}

void CSubDlgRemoteRec::OnBnClickedButtonPlayback()
{
	g_pMainDlg->ShowMsg("开始回放...");
    SetDlgItemText(IDC_EDIT_CURRENTTIME, CString(""));
	AfxBeginThread(StartBThread,this);
}

void CSubDlgRemoteRec::OnBnClickedButtonStopplayb()
{
	g_pMainDlg->ShowMsg("停止回放...");
	AfxBeginThread(StopBThread,this);
}

void CSubDlgRemoteRec::OnBnClickedButtonGetcurrenttime()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");

		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	VIDEO_INT64 llCurTime = -1;
	llCurTime = Video_GetCurrentPlayTime(g_pMainDlg->m_lRePlayHandleR);
    if (llCurTime > -1)
    {
        SetDlgItemInt(IDC_EDIT_CURRENTTIME, llCurTime);
    }

	g_pMainDlg->PrintCallMsg("Video_GetCurrentPlayTime()|获取当前播放时间戳", Video_GetLastError());
}

void CSubDlgRemoteRec::OnBnClickedButtonLocateplay()
{
	g_pMainDlg->ShowMsg("定位播放...");
	AfxBeginThread(LocatPlayThread,this);
}

void CSubDlgRemoteRec::OnBnClickedButtonStopdl()
{
	//int iRet = -1;
	//iRet = Video_StopDownload(g_pMainDlg->m_lDownloadHandle);
	//g_pMainDlg->PrintCallMsg("Video_StopDownload()", iRet);
	//if (iRet == VIDEO_ERR_SUCCESS)
	//{
	//	g_pMainDlg->m_lDownloadHandle = -1;
	//}
}

void CSubDlgRemoteRec::OnBnClickedButtonDownload()
{
	//CString csUrl, csRecPath, csStartTM, csEndTM;
	//long lMaxFileSize = GetDlgItemInt(IDC_EDIT_MAXSIZE);
	//GetDlgItemText(IDC_EDIT_RECORDURL, csUrl);
	//GetDlgItemText(IDC_EDIT_RECORDT, csRecPath);
	//string url = AnsiToUtf8(csUrl.GetBuffer());
	//string cspath = AnsiToUtf8(csRecPath.GetBuffer());

	//struct tm tmStart;
	//memset(&tmStart,0,sizeof(tmStart));
	//struct tm tmEnd;
	//memset(&tmEnd,0,sizeof(tmEnd));
	//CTime ctTemp;

	//m_StartDateDL.GetTime(ctTemp);
	//tmStart.tm_year = ctTemp.GetYear() - 1900;
	//tmStart.tm_mon  = ctTemp.GetMonth() - 1;
	//tmStart.tm_mday = ctTemp.GetDay();
	//m_StartTimeDL.GetTime(ctTemp);
	//tmStart.tm_hour = ctTemp.GetHour();
	//tmStart.tm_min  = ctTemp.GetMinute();
	//tmStart.tm_sec  = ctTemp.GetSecond();
	//time_t llStartTime = mktime(&tmStart);

	//m_EndDateDL.GetTime(ctTemp);
	//tmEnd.tm_year = ctTemp.GetYear() - 1900;
	//tmEnd.tm_mon  = ctTemp.GetMonth() - 1;
	//tmEnd.tm_mday = ctTemp.GetDay();
	//m_EndTimeDL.GetTime(ctTemp);
	//tmEnd.tm_hour = ctTemp.GetHour();
	//tmEnd.tm_min  = ctTemp.GetMinute();
	//tmEnd.tm_sec  = ctTemp.GetSecond();
	//time_t llEndTime = mktime(&tmEnd);
	//
	//if (g_pMainDlg->m_lDownloadHandle < 0)
	//{
	//	VIDEO_DOWNLOAD_REQ stDlReq;
	//	stDlReq.i64MaxFileSize = 0/*lMaxFileSize*/;
	//	memset(stDlReq.szFileName, 0x00, sizeof(stDlReq.szFileName));
	//	strcpy(stDlReq.szFileName, csRecPath.GetBuffer());
	//	stDlReq.fnProgress = ProgressCallback;

	//	VIDEO_INT64 llRet = -1;
	//	//llRet = Video_StartDownload(csUrl.GetBuffer(), llStartTime, llEndTime, &stDlReq);
	//	g_pMainDlg->PrintCallMsg("Video_StartDownload()", llRet);

	//	if (llRet >= 0)
	//	{
	//		//CString csMsg;
	//		//csMsg.Format("录像路径:%s", csRecPath.GetBuffer());
	//		g_pMainDlg->m_lDownloadHandle = llRet;
	//		//g_pMainDlg->ShowMsg(csMsg);
	//	}
	//}
}

void CSubDlgRemoteRec::OnBnClickedButtonGetvol()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		return;
	}
	int iVol = -1;
	iVol = Video_GetVolume(g_pMainDlg->m_lRePlayHandleR);
	if (iVol != -1)
	{
		CString csVol;
		csVol.Format("%d", iVol);
		GetDlgItem(IDC_EDIT_GETVOL2)->SetWindowText(csVol);
	}

    g_pMainDlg->PrintCallMsg("Video_GetVolume()|获取音量", Video_GetLastError());
}

void CSubDlgRemoteRec::OnBnClickedButtonSetvol()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		return;
	}
	int iVol = GetDlgItemInt(IDC_EDIT_SETVOL2, NULL, 1);
	Video_SetVolume(g_pMainDlg->m_lRePlayHandleR, iVol);
    g_pMainDlg->PrintCallMsg("Video_SetVolume()|设置音量", Video_GetLastError());
}

void CSubDlgRemoteRec::OnBnClickedButtonAudioon2()
{
	int iRet = -1;
	iRet = Video_SoundCtrl(g_pMainDlg->m_lRePlayHandleR, 0);
	g_pMainDlg->PrintCallMsg("Video_SoundCtrl()|打开声音", Video_GetLastError());
}

void CSubDlgRemoteRec::OnBnClickedButtonAudiooff2()
{
	int iRet = -1;
	iRet = Video_SoundCtrl(g_pMainDlg->m_lRePlayHandleR, 1);
	g_pMainDlg->PrintCallMsg("Video_SoundCtrl()|关闭声音", Video_GetLastError());
}

void CSubDlgRemoteRec::ShowUISpeed()
{
	CString csSpeed;
	switch (m_iSpeedRet)
	{
	case -4:	csSpeed = "-16";	break;
	case -3:	csSpeed = "-8";		break;
	case -2:	csSpeed = "-4";		break;
	case -1:	csSpeed = "-2";		break;
	case 0:		csSpeed = "1";		break;
	case 1:		csSpeed = "2";		break;
	case 2:		csSpeed = "4";		break;
	case 3:		csSpeed = "8";		break;
	case 4:		csSpeed = "16";		break;
	default:	break;
	}
	GetDlgItem(IDC_EDIT_SPEED)->SetWindowText(csSpeed);
}
void CSubDlgRemoteRec::OnBnClickedButtonSlow()
{
	if (m_iSpeedRet <= -4)
	{
		m_iSpeedRet = -4;
		return;
	}
	-- m_iSpeedRet;
	ShowUISpeed();
}

void CSubDlgRemoteRec::OnBnClickedButtonRapid()
{
	if (m_iSpeedRet >= 4)
	{
		m_iSpeedRet = 4;
		return;
	}
	++ m_iSpeedRet;
	ShowUISpeed();
}

void CSubDlgRemoteRec::OnBnClickedButtonSpeedplay()
{
	AfxBeginThread(SpeedPlayThread,this);
}

int CSubDlgRemoteRec::Fun_SpeedPlay()
{
	int iSpeed = 0;
	switch (m_iSpeedRet)
	{
	case -4:	iSpeed = -16;	break;
	case -3:	iSpeed = -8;	break;
	case -2:	iSpeed = -4;	break;
	case -1:	iSpeed = -2;	break;
	case 0:		iSpeed = 1;		break;
	case 1:		iSpeed = 2;		break;
	case 2:		iSpeed = 4;		break;
	case 3:		iSpeed = 8;		break;
	case 4:		iSpeed = 16;	break;
	default:	break;
	}

	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");
		return 0;
	}
	int iRet = -1;
	iRet = Video_PlayCtrl(g_pMainDlg->m_lRePlayHandleR, 3, iSpeed);
	CString csMsg;
	csMsg.Format("Video_PlayCtrl()|倍速播放:%d", iSpeed);
	g_pMainDlg->PrintCallMsg(csMsg.GetBuffer(), Video_GetLastError());
    return 0;
}

int CSubDlgRemoteRec::Fun_LocatPlay()
{
	if ( g_pMainDlg->m_lRePlayHandleR < 0 )
	{
		g_pMainDlg->ShowMsg("未开始网络录像回放");
		return 0;
	}
	long lLocate = GetDlgItemInt(IDC_EDIT_LOCATETIME);
	int iRet = -1;
	iRet = Video_PlayCtrl(g_pMainDlg->m_lRePlayHandleR, 2, lLocate);
	g_pMainDlg->PrintCallMsg("Video_PlayCtrl()|定位播放", Video_GetLastError());
    return 0;
}
