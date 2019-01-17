#pragma once

#include "afxcmn.h"
#include "afxwin.h"

class CSubDlgReal : public CDialog
{
	// Construction
public:
	CSubDlgReal(CWnd* pParent = NULL);   // standard constructor

	int		m_nWndSel;
	enum
	{
		IDD = IDD_DLG_SUB_REAL
	};

	CStatic	m_wnd3;
	CStatic	m_wnd2;
	CStatic	m_wnd1;
	CStatic	m_wnd0;

	CStatic *sta[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStartreal();
	afx_msg void OnButtonStopreal();
	afx_msg void OnStaticWnd0();
	afx_msg void OnStaticWnd1();
	afx_msg void OnStaticWnd2();
	afx_msg void OnStaticWnd3();

	afx_msg void OnButtonPiccapture();
	DECLARE_MESSAGE_MAP()
public:

	//BOOL m_startRect;   //绘制矩形框标志 
	//CPoint m_startPoint; //矩形框开始点 
	//CPoint m_OldPoint;   //矩形框终点（但是它是上一次的点，所以这里用了Old标识）

	//int bCounter;

	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CComboBox m_combox;
	afx_msg void OnBnClickedButtonGetvol();
	afx_msg void OnBnClickedButtonSetvol();
	afx_msg void OnBnClickedButtonAudioon();
	afx_msg void OnBnClickedButtonAudiooff();

public:
	int Fun_StartPlay();
	int Fun_StopPlay();
	CString GetModuleDir();
};
