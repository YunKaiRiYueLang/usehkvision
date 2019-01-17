#pragma once


#include <string>
#include "stdafx.h"
#include "SubDlgInit.h"
#include "SubDlgLocalRec.h"
#include "SubDlgReal.h"
#include "SubDlgRemoteRec.h"

using namespace std;

extern char startpath[MAX_PATH];

string AnsiToUtf8(LPCSTR Ansi);
string Utf8toAnsi(LPCSTR utf8);


//�����ص�
void CALLBACK StreamCallBack(VIDEO_INT64 i64PlayHandle, int iStreamDataType, const char* pDataArray, int iDataLen, void* pUserData);
//YUV���ݻص�
void CALLBACK DecodedDataCallback(VIDEO_INT64 i64PlayHandle, const char* pDataArray, int iDataLen, int iWidth, int iHeight, int iFrameType, int iTimeStamp, void* pUserData);
//��Ϣ�ص�
void CALLBACK MsgCallBack(VIDEO_INT64 i64PlayHandle, int iMsg, void* pUserData);

class CAPIDemoDlg : public CDialog
{
	// Construction
public:
	CAPIDemoDlg(CWnd* pParent = NULL);	// standard constructor

	void	ShowMsg(CString csMsg);
	void    PrintCallMsg(char* csFunc, long lVal);
	void	CreateTab(void);

	VIDEO_INT64		m_lPlayHandle[4];			//ʵʱԤ��ʵ����
	VIDEO_INT64		m_lRePlayHandleR;			//Զ�̻ط�ʵ����			
	VIDEO_INT64     m_lDownloadHandle;			//Զ������ʵ����

	LONG	m_lRecHandle[4];			//ʵʱ��Ƶ¼��ʵ����	
	LONG	m_lRePlayHandleL;			//���ػط�ʵ����

	CSubDlgInit m_dlgInit;
	//CSubDlgLocalRec m_dlgLocalRec;
	CSubDlgReal m_dlgReal;
	CSubDlgRemoteRec m_dlgRemoteRec;

	enum
	{
		IDD = IDD_APIDEMO_DIALOG
	};

	CTabCtrl	m_tabOperate;
	CEdit	m_ctrlMsg;
	BOOL IsSaveBmp;
	CListBox m_listbox;
    time_t time4Stream;
    time_t time4YUV;
    time_t time4Msg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    afx_msg void OnTimer(UINT uID);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabOperate(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnDblclkList1();
	afx_msg LRESULT OnCallbackmsg(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnShowMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnClose();
};
