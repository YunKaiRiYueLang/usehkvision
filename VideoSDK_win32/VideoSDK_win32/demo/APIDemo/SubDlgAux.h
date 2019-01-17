#pragma once

class CSubDlgAux : public CDialog
{
public:
	CSubDlgAux(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_DLG_SUB_AUX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGeterror();
	DECLARE_MESSAGE_MAP()
};
