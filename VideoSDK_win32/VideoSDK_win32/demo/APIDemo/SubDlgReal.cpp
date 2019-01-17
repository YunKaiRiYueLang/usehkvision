// SubDlgReal.cpp : implementation file
//

#include "stdafx.h"
#include "APIDemo.h"
#include "SubDlgReal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgReal dialog

CSubDlgReal::CSubDlgReal(CWnd* pParent /*=NULL*/)
: CDialog(CSubDlgReal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgReal)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nWndSel = 0;
}


void CSubDlgReal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgReal)
	DDX_Control(pDX, IDC_STATIC_WND3, m_wnd3);
	DDX_Control(pDX, IDC_STATIC_WND2, m_wnd2);
	DDX_Control(pDX, IDC_STATIC_WND1, m_wnd1);
	DDX_Control(pDX, IDC_STATIC_WND0, m_wnd0);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO3, m_combox);
}


BEGIN_MESSAGE_MAP(CSubDlgReal, CDialog)
	//{{AFX_MSG_MAP(CSubDlgReal)
	ON_BN_CLICKED(IDC_BUTTON_STARTREAL, OnButtonStartreal)
	ON_BN_CLICKED(IDC_BUTTON_STOPREAL, OnButtonStopreal)
	ON_BN_CLICKED(IDC_STATIC_WND0, OnStaticWnd0)
	ON_BN_CLICKED(IDC_STATIC_WND1, OnStaticWnd1)
	ON_BN_CLICKED(IDC_STATIC_WND2, OnStaticWnd2)
	ON_BN_CLICKED(IDC_STATIC_WND3, OnStaticWnd3)
	ON_BN_CLICKED(IDC_BUTTON_PICCAPTURE, OnButtonPiccapture)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_GETVOL, &CSubDlgReal::OnBnClickedButtonGetvol)
	ON_BN_CLICKED(IDC_BUTTON_SETVOL, &CSubDlgReal::OnBnClickedButtonSetvol)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOON, &CSubDlgReal::OnBnClickedButtonAudioon)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOOFF, &CSubDlgReal::OnBnClickedButtonAudiooff)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgReal message handlers

CString CSubDlgReal::GetModuleDir() 
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

BOOL CSubDlgReal::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString csCapPath = GetModuleDir() + "\\test_pic";
	GetDlgItem(IDC_EDIT_PICPATH)->SetWindowText(csCapPath);
	GetDlgItem(IDC_EDIT_CAMID)->SetWindowText("");

	//lRet = -1;

	sta[3] = &m_wnd3;
	sta[2] = &m_wnd2;
	sta[1] = &m_wnd1;
	sta[0] = &m_wnd0;

	//m_startRect = FALSE;
	//bCounter = 0;

	m_combox.InsertString(0, "jpg");
	m_combox.InsertString(1, "bmp");


	m_combox.SetCurSel(0);
	return TRUE;
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgReal::OnStaticWnd0()
{
	m_nWndSel = 0;
}

void CSubDlgReal::OnStaticWnd1()
{
	m_nWndSel = 1;
}

void CSubDlgReal::OnStaticWnd2()
{
	m_nWndSel = 2;
}

void CSubDlgReal::OnStaticWnd3()
{
	m_nWndSel = 3;
}


UINT StartRThread(LPVOID lparam)
{
	CSubDlgReal* pDlg = (CSubDlgReal*)lparam;
	pDlg->Fun_StartPlay();

	return 0;
}
UINT StopRThread(LPVOID lparam)
{
	CSubDlgReal* pDlg = (CSubDlgReal*)lparam;
	pDlg->Fun_StopPlay();

	return 0;
}

int CSubDlgReal::Fun_StartPlay()
{
	CString csUrl;
	GetDlgItemText(IDC_EDIT_CAMID, csUrl);
	VIDEO_INT64 llRet = -1;
	if ( g_pMainDlg->m_lPlayHandle[0] < 0 )
	{
		USERDATA stUserData;
		stUserData.ctype = RealPlay;
		strcpy_s(stUserData.msg, AnsiToUtf8("ʵʱ").c_str());
		VIDEO_PLAY_REQ stReq;
		stReq.fnStream = StreamCallBack;
		stReq.fnDecodedStream = DecodedDataCallback;
		stReq.fnMsg = MsgCallBack;
		stReq.pUserData = (void*)&stUserData;
		CButton *pBtn2 = (CButton *)GetDlgItem(IDC_CHECK2);
		if (pBtn2->GetCheck())
		{
			stReq.iHardWareDecode = 1;
		}
		else
		{
			stReq.iHardWareDecode = 0;
		}
		CButton *pBtn1 = (CButton *)GetDlgItem(IDC_CHECK1);
		if (pBtn1->GetCheck())
		{
			llRet = Video_StartPreview(csUrl.GetBuffer(),
				*sta[0],
				&stReq);
		}
		else
		{
			llRet = Video_StartPreview(csUrl.GetBuffer(),
				NULL,
				&stReq);
		}

		g_pMainDlg->m_lPlayHandle[0] = llRet;
	}

	g_pMainDlg->PrintCallMsg("Video_StartPreview()", Video_GetLastError());

	return 0;
}

int CSubDlgReal::Fun_StopPlay()
{
	int iRet = -1;

	iRet = Video_StopPreview(g_pMainDlg->m_lPlayHandle[0]);

	g_pMainDlg->PrintCallMsg("Video_StopPreview()", Video_GetLastError());

	if ( iRet >= 0 )
	{
		g_pMainDlg->m_lPlayHandle[0] = -1;

		sta[0]->Invalidate();
	}
	return 0;
}
void CSubDlgReal::OnButtonStartreal()
{
	g_pMainDlg->ShowMsg("��ʼԤ��...");
	AfxBeginThread(StartRThread,this);
}

void CSubDlgReal::OnButtonStopreal()
{
	g_pMainDlg->ShowMsg("ֹͣԤ��...");
	AfxBeginThread(StopRThread,this);
}

void CSubDlgReal::OnButtonPiccapture()
{
	CString csPic;
	GetDlgItemText(IDC_EDIT_PICPATH, csPic);
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
	iRet = Video_PlaySnap(g_pMainDlg->m_lPlayHandle[0], strPath.c_str());

	g_pMainDlg->PrintCallMsg("Video_PlaySnap()|ץͼ", Video_GetLastError());

}

//void CSubDlgReal::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CClientDC dc(this);
//	dc.SetROP2(R2_NOT);
//	dc.SelectStockObject(NULL_BRUSH);
//	dc.Rectangle(CRect(m_startPoint, m_OldPoint));
//
//	ZeroMemory(&m_startPoint, sizeof(CPoint));
//	ZeroMemory(&m_OldPoint, sizeof(CPoint));
//
//	CRect wndrc;
//	CString msg;
//
//	::GetWindowRect(sta[0]->GetSafeHwnd(), &wndrc);
//
//	ClientToScreen(&point);
//
//	if ( PtInRect(&wndrc, point) )
//	{
//		ClipCursor(&wndrc);
//		msg.Format("OnLButtonDown In x= %d, y= %d", point.x, point.y);
//	}
//	else
//	{
//		msg.Format("OnLButtonDown Out x= %d, y= %d", point.x, point.y);
//		return;
//	}
//
//	ScreenToClient(&point);
//
//	m_startRect = TRUE;   //���������������ÿ��Կ�ʼ���ƾ��ο� 
//	m_startPoint = point; //��¼��ʼ�� 
//	m_OldPoint = point;   //�����ϵ�ҲΪ��ʼ��
//
//	CDialog::OnLButtonDown(nFlags, point);
//}
//
//
//void CSubDlgReal::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	if ( !m_startRect )
//	{
//		return;
//	}
//
//	CPoint m_s = m_startPoint;
//	CPoint m_o = m_OldPoint;
//
//	ClientToScreen(&m_s);
//	ClientToScreen(&m_o);
//
//	sta[0]->ScreenToClient(&m_s);
//	sta[0]->ScreenToClient(&m_o);
//
//	int left2right = m_o.x - m_s.x;
//	int top2bottom = m_o.y - m_s.y;
//
//	bCounter = 0;
//
//	if ( left2right > 2 && top2bottom > 2 ) //����
//	{
//		bCounter = 4;
//	}
//	else if ( left2right < 2 && top2bottom > 2 )//����
//	{
//		bCounter = 3;
//	}
//	else if ( left2right > 2 && top2bottom < 2 )//����
//	{
//		bCounter = 2;
//	}
//	else if ( left2right < 2 && top2bottom < 2 )//����
//	{
//		bCounter = 1;
//	}
//
//	CString csID;
//	GetDlgItemText(IDC_EDIT_CAMID, csID);
//
//	CRect wndrc;
//	::GetWindowRect(sta[0]->GetSafeHwnd(), &wndrc);
//
//
//	int w = wndrc.Width();
//	int h = wndrc.Height();
//
//	int xTop = 352 * m_s.x / wndrc.Width();
//	int yTop = 288 * m_s.y / wndrc.Height();
//	int xBottom = 352 * m_o.x / wndrc.Width();
//	int yBottom = 288 * m_o.y / wndrc.Height();
//
//
//	if ( (abs(left2right) > 2) && (abs(top2bottom) > 2) )
//	{
//		lRet = Std_PtzCtrl3D(g_pMainDlg->m_lLoginID,
//							 csID.GetBuffer(),
//							 xTop, yTop, xBottom, yBottom,
//							 bCounter);
//
//		g_pMainDlg->PrintCallMsg("Std_PtzCtrl()", lRet);
//	}
//
//	////��������һ�����Σ���ԭ����϶�ʱ���ο����ԭ����ͬ��
//	//CClientDC dc(this);
//	//dc.SetROP2(R2_NOT);
//	//dc.SelectStockObject(NULL_BRUSH);
//	//dc.Rectangle(CRect(m_startPoint, m_OldPoint));
//
//	m_startRect = FALSE; //���û��ƾ��ο��־ 
//	ClipCursor(NULL);
//
//	CDialog::OnLButtonUp(nFlags, point);
//
//}
//
//
//void CSubDlgReal::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CClientDC dc(this);   //��ȡ�豸��� 
//	//SetRop2 Specifies the new drawing mode.(MSDN) 
//	//R2_NOT   Pixel is the inverse of the screen color.(MSDN) 
//	//�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ 
//	//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£� 
//	//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ� 
//	//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ������ˣ� 
//
//	CRect wndrc;
//	CString msg;
//
//	::GetWindowRect(sta[0]->GetSafeHwnd(), &wndrc);
//
//	ScreenToClient(&wndrc);
//
//	if ( PtInRect(&wndrc, point) )
//	{
//		msg.Format("OnMouseMove In x= %d, y= %d", point.x, point.y);
//	}
//	else
//	{
//		msg.Format("OnMouseMove Out x= %d, y= %d", point.x, point.y);
//	}
//
//	SetWindowText(msg.GetBuffer());
//
//	dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!! 
//	dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ 
//
//	if ( TRUE == m_startRect )   //�����Ƿ��е����ж��Ƿ���Ի����� 
//	{
//		dc.Rectangle(CRect(m_startPoint, m_OldPoint));
//		dc.Rectangle(CRect(m_startPoint, point));
//
//		m_OldPoint = point;
//	}
//
//	CDialog::OnMouseMove(nFlags, point);
//}

void CSubDlgReal::OnBnClickedButtonGetvol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( g_pMainDlg->m_lPlayHandle[0] < 0 )
	{
		return;
	}
	int iVol = -1;
	iVol = Video_GetVolume(g_pMainDlg->m_lPlayHandle[0]);
	if (iVol != -1)
	{
		CString csVol;
		csVol.Format("%d", iVol);
		GetDlgItem(IDC_EDIT_GETVOL)->SetWindowText(csVol);
	}

    g_pMainDlg->PrintCallMsg("Video_GetVolume()|��ȡ����", Video_GetLastError());
}

void CSubDlgReal::OnBnClickedButtonSetvol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( g_pMainDlg->m_lPlayHandle[0] < 0 )
	{
		return;
	}
	int iVol = GetDlgItemInt(IDC_EDIT_SETVOL, NULL, 1);
	//GetDlgItem(IDC_EDIT_SETVOL)->GetDlgItemInt(iVol);
	Video_SetVolume(g_pMainDlg->m_lPlayHandle[0], iVol);
    g_pMainDlg->PrintCallMsg("Video_SetVolume()|��������", Video_GetLastError());
}

void CSubDlgReal::OnBnClickedButtonAudioon()
{
	int iRet = -1;
	iRet = Video_SoundCtrl(g_pMainDlg->m_lPlayHandle[0], 0);
	g_pMainDlg->PrintCallMsg("Video_SoundCtrl()|������", Video_GetLastError());	
}

void CSubDlgReal::OnBnClickedButtonAudiooff()
{
	int iRet = -1;
	iRet = Video_SoundCtrl(g_pMainDlg->m_lPlayHandle[0], 1);
	g_pMainDlg->PrintCallMsg("Video_SoundCtrl()|�ر�����", Video_GetLastError());	
}
