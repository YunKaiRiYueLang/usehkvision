//// SubDlgLocalRec.cpp : implementation file
////
//
#include "stdafx.h"
//#include "APIDemo.h"
//#include "SubDlgLocalRec.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
///////////////////////////////////////////////////////////////////////////////
//// CSubDlgLocalRec dialog
//
//
//
//CSubDlgLocalRec::CSubDlgLocalRec(CWnd* pParent /*=NULL*/)
//: CDialog(CSubDlgLocalRec::IDD, pParent)
//{
//	//{{AFX_DATA_INIT(CSubDlgLocalRec)
//	// NOTE: the ClassWizard will add member initialization here
//	//}}AFX_DATA_INIT
//}
//
//
//void CSubDlgLocalRec::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//{{AFX_DATA_MAP(CSubDlgLocalRec)
//	DDX_Control(pDX, IDC_STATIC_RPWND, m_wndV);
//	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_COMBO1, m_combox);
//}
//
//
//BEGIN_MESSAGE_MAP(CSubDlgLocalRec, CDialog)
//	//{{AFX_MSG_MAP(CSubDlgLocalRec)
//	ON_BN_CLICKED(IDC_BUTTON_STARTFRP, OnButtonStartfrp)
//	ON_BN_CLICKED(IDC_BUTTON_STOPFRP, OnButtonStopfrp)
//	ON_BN_CLICKED(IDC_BUTTON_GETFRPPOS, OnButtonGetfrppos)
//	ON_BN_CLICKED(IDC_BUTTON_GETTOTALTM, OnButtonGettotaltm)
//	ON_BN_CLICKED(IDC_BUTTON_SETRPPOS, OnButtonSetrppos)
//	ON_BN_CLICKED(IDC_BUTTON_FILECUT, OnButtonFilecut)
//	ON_BN_CLICKED(IDC_BUTTON_RPPAUSE, OnButtonRppause)
//	ON_BN_CLICKED(IDC_BUTTON_RPSTOP, OnButtonRpstop)
//	ON_BN_CLICKED(IDC_BUTTON_RPFRAMEF, OnButtonRpframef)
//	ON_BN_CLICKED(IDC_BUTTON_RPFRAMEB, OnButtonRpframeb)
//	ON_BN_CLICKED(IDC_BUTTON_PICCAPTURE3, &CSubDlgLocalRec::OnBnClickedButtonPiccapture3)
//	ON_BN_CLICKED(IDC_BUTTON_RESUME, &CSubDlgLocalRec::OnBnClickedButtonResume)
//	ON_BN_CLICKED(IDC_BUTTON_FORWARDP2, &CSubDlgLocalRec::OnBnClickedButtonForwardp2)
//	ON_BN_CLICKED(IDC_BUTTON_FORWARDP4, &CSubDlgLocalRec::OnBnClickedButtonForwardp4)
//	ON_BN_CLICKED(IDC_BUTTON_FORWARDP8, &CSubDlgLocalRec::OnBnClickedButtonForwardp8)
//	ON_BN_CLICKED(IDC_BUTTON_FORWARDP16, &CSubDlgLocalRec::OnBnClickedButtonForwardp16)
//	ON_BN_CLICKED(IDC_BUTTON_BACKP2, &CSubDlgLocalRec::OnBnClickedButtonBackp2)
//	ON_BN_CLICKED(IDC_BUTTON_BACKP4, &CSubDlgLocalRec::OnBnClickedButtonBackp4)
//	ON_BN_CLICKED(IDC_BUTTON_BACKP8, &CSubDlgLocalRec::OnBnClickedButtonBackp8)
//	ON_BN_CLICKED(IDC_BUTTON_BACKP16, &CSubDlgLocalRec::OnBnClickedButtonBackp16)
//	ON_BN_CLICKED(IDC_BUTTON_FORWARDP1, &CSubDlgLocalRec::OnBnClickedButtonForwardp1)
//	ON_BN_CLICKED(IDC_BUTTON_BACKP1, &CSubDlgLocalRec::OnBnClickedButtonBackp1)
//END_MESSAGE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CSubDlgLocalRec message handlers
//
//BOOL CSubDlgLocalRec::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//
//	GetDlgItem(IDC_EDIT_RECORDPATH)->SetWindowText("C:\\");
//	GetDlgItem(IDC_EDIT_POSTIME)->SetWindowText("10");
//	GetDlgItem(IDC_EDIT_SOURCEFILE)->SetWindowText("C:\\");
//	GetDlgItem(IDC_EDIT_DESTINATIONFILE)->SetWindowText("C:\\");
//	GetDlgItem(IDC_EDIT_STARTTMCUT)->SetWindowText("0");
//	GetDlgItem(IDC_EDIT_ENDTMCUT)->SetWindowText("20");
//
//	m_combox.InsertString(0, "0:jpg");
//	m_combox.InsertString(1, "1:bmp");
//
//	m_combox.SetCurSel(0);
//
//	//g_SubDlg = this;
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// EXCEPTION: OCX Property Pages should return FALSE
//}
//
//void CSubDlgLocalRec::OnButtonStartfrp()
//{
//	CString csFile;
//
//	GetDlgItemText(IDC_EDIT_RECORDPATH, csFile);
//
//	long lRet = -1;
//
//	//char szBuf[1204] = { 0 };
//	//strcpy_s(szBuf, AnsiToUtf8(czFile));
//
//	string cfile = AnsiToUtf8(csFile.GetBuffer());
//
//	CButton *m_handle = (CButton *)GetDlgItem(IDC_CHECK1);
//	if ( m_handle->GetCheck() )
//	{
//		//lRet = Std_StartFileReplay((char*)cfile.c_str(), m_wndV, StreamCallBack, NULL);
//	}
//	else
//	{
//		//lRet = Std_StartFileReplay((char*)cfile.c_str(), NULL, StreamCallBack, NULL);
//	}
//
//	g_pMainDlg->PrintCallMsg("Std_StartFileReplay()", lRet);
//
//	if ( lRet >= 0 )
//	{
//		g_pMainDlg->m_lRePlayHandleL = lRet;
//	}
//}
//
//void CSubDlgLocalRec::OnButtonStopfrp()
//{
//	long lRet = -1;
//
//	lRet = Std_StopFileReplay(g_pMainDlg->m_lRePlayHandleL);
//
//	g_pMainDlg->PrintCallMsg("Std_StopFileReplay()", lRet);
//
//	if ( lRet >= 0 )
//	{
//		g_pMainDlg->m_lRePlayHandleL = -1;
//		m_wndV.Invalidate();
//	}
//}
//
//void CSubDlgLocalRec::OnButtonGetfrppos()
//{
//	long lRet = -1;
//	long lPlayTimed = 0;
//
//	lRet = Std_GetFileReplayPos(g_pMainDlg->m_lRePlayHandleL, &lPlayTimed);
//
//	g_pMainDlg->PrintCallMsg("Std_GetFileReplayPos()", lRet);
//
//	if ( lRet >= 0 )
//	{
//		CString csMsg;
//
//		csMsg.Format("录像已经回放%d秒", lPlayTimed);
//
//		g_pMainDlg->ShowMsg(csMsg);
//	}
//}
//
//void CSubDlgLocalRec::OnButtonGettotaltm()
//{
//	long lRet = -1;
//	long lTotalTime = 0;
//
//	lRet = Std_GetFileTotalTime(g_pMainDlg->m_lRePlayHandleL, &lTotalTime);
//
//	g_pMainDlg->PrintCallMsg("Std_GetFileTotalTime()", lRet);
//
//	if ( lRet >= 0 )
//	{
//		CString csMsg;
//
//		csMsg.Format("本次录像总回放时间为%d秒", lTotalTime);
//
//		g_pMainDlg->ShowMsg(csMsg);
//	}
//}
//
//void CSubDlgLocalRec::OnButtonSetrppos()
//{
//	long lRet = -1;
//	long lPlayTime = 0;
//	CString msg;
//
//	lPlayTime = GetDlgItemInt(IDC_EDIT_POSTIME);
//
//	lRet = Std_SetStreamReplayPos(g_pMainDlg->m_lRePlayHandleL, lPlayTime);
//
//	msg.Format("%d", lPlayTime);
//
//	SetDlgItemTextA(IDC_EDIT_POSTIME, msg.GetBuffer());
//
//	g_pMainDlg->PrintCallMsg("Std_SetStreamReplayPos()", lRet);
//}
//
//void CSubDlgLocalRec::OnButtonFilecut()
//{
//	long lRet = -1;
//	long lBeginTime = 0, lEndTime = 0;
//	CString csSrc, csDes;
//
//	lBeginTime = GetDlgItemInt(IDC_EDIT_STARTTMCUT);
//	lEndTime = GetDlgItemInt(IDC_EDIT_ENDTMCUT);
//	GetDlgItemText(IDC_EDIT_SOURCEFILE, csSrc);
//	GetDlgItemText(IDC_EDIT_DESTINATIONFILE, csDes);
//
//	string src = AnsiToUtf8(csSrc.GetBuffer());
//
//	string des = AnsiToUtf8(csDes.GetBuffer());
//
//	lRet = Std_FileCut(src.c_str(), des.c_str(), lBeginTime, lEndTime);
//
//	g_pMainDlg->PrintCallMsg("Std_FileCut()", lRet);
//}
//
//void CSubDlgLocalRec::OnButtonRppause()
//{
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_PAUSE);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|Pause", lRet);
//
//	return;
//
//	/*CString csTxt;
//	((CButton*)GetDlgItem(IDC_BUTTON_RPPAUSE))->GetWindowText(csTxt);
//
//	if ( csTxt.Compare("暂停") >= 0 )
//	{
//		((CButton*)GetDlgItem(IDC_BUTTON_RPPAUSE))->SetWindowText("恢复");
//
//		lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_PAUSE);
//
//		g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|Pause", lRet);
//	}
//	else
//	{
//		((CButton*)GetDlgItem(IDC_BUTTON_RPPAUSE))->SetWindowText("暂停");
//
//		lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_RESUME);
//
//		g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|Resume", lRet);
//	}*/
//}
//
//void CSubDlgLocalRec::OnButtonRpstop()
//{
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_STOP);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|Stop", lRet);
//}
//
//void CSubDlgLocalRec::OnButtonRpframef()
//{
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_ONEBYONE);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|OneFrameByone", lRet);
//}
//
//void CSubDlgLocalRec::OnButtonRpframeb()
//{
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_ONEBYONEBACK);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|OneFrameBack", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonPiccapture3()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	CString csPic;
//	CString csMsg;
//	int nPicFormat;
//
//	GetDlgItemText(IDC_EDIT_PICPATH4, csPic);
//	//nPicFormat = GetDlgItemInt(IDC_EDIT_PICFORMAT3);
//
//	int index = m_combox.GetCurSel();
//
//	long lRet = -1;
//
//	string	szBuf = AnsiToUtf8(csPic.GetBuffer());
//
//	lRet = Std_Capture(g_pMainDlg->m_lRePlayHandleL, szBuf.c_str(), index);
//
//	g_pMainDlg->m_lRecHandle[0] = lRet;
//
//	g_pMainDlg->PrintCallMsg("Std_Capture()", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonResume()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_RESUME);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|Resume", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonForwardp2()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_2_FORWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|2倍速播放", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonForwardp4()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//	
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_4_FORWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|4倍速播放", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonForwardp8()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_8_FORWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|8倍速播放", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonForwardp16()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_16_FORWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|16倍速播放", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonBackp2()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_2_BACKWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|2倍速回退", lRet);
//
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonBackp4()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_4_BACKWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|4倍速回退", lRet);
//
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonBackp8()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_8_BACKWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|8倍速回退", lRet);
//
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonBackp16()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_16_BACKWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|16倍速回退", lRet);
//
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonForwardp1()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_1_FORWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|正常倍速播放", lRet);
//}
//
//
//void CSubDlgLocalRec::OnBnClickedButtonBackp1()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	if ( g_pMainDlg->m_lRePlayHandleL < 0 )
//	{
//		g_pMainDlg->ShowMsg("call Std_FileReplayControl(),未开始本地播放");
//
//		return;
//	}
//
//	long lRet = -1;
//
//	lRet = Std_FileReplayControl(g_pMainDlg->m_lRePlayHandleL, PLAYMODE_1_BACKWARD);
//
//	g_pMainDlg->PrintCallMsg("Std_FileReplayControl()|正常倍速回退", lRet);
//}
