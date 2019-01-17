#pragma once
#include "afxwin.h"
#include "afxdtctl.h"

class CSubDlgRemoteRec : public CDialog
{
public:
	CSubDlgRemoteRec(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_DLG_SUB_REMOTEREC };
	CStatic	m_wndRP;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	int Fun_StartPlay();
	int Fun_StopPlay();
	int Fun_SpeedPlay();
	int Fun_LocatPlay();

private:
	CString GetModuleDir();
	void ShowUISpeed();

public:
	int m_iSpeedRet;
	CComboBox m_combox;

	afx_msg void OnBnClickedButtonPiccapture2();	
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonResume();
	afx_msg void OnBnClickedButtonLocateplay();

	afx_msg void OnBnClickedButtonPlayback();
	afx_msg void OnBnClickedButtonStopplayb();
	afx_msg void OnBnClickedButtonGetcurrenttime();

	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonStopdl();	
	afx_msg void OnBnClickedButtonGetvol();
	afx_msg void OnBnClickedButtonSetvol();

	CDateTimeCtrl m_StartDatePB;
	CDateTimeCtrl m_StartTimePB;
	CDateTimeCtrl m_EndDatePB;
	CDateTimeCtrl m_EndTimePB;
	CDateTimeCtrl m_StartDateDL;
	CDateTimeCtrl m_StartTimeDL;
	CDateTimeCtrl m_EndDateDL;
	CDateTimeCtrl m_EndTimeDL;
	afx_msg void OnBnClickedButtonAudioon2();
	afx_msg void OnBnClickedButtonAudiooff2();
	afx_msg void OnBnClickedButtonSlow();
	afx_msg void OnBnClickedButtonRapid();
	afx_msg void OnBnClickedButtonSpeedplay();
};
