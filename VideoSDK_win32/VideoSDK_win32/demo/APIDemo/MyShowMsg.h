#pragma once

#include "stdafx.h"
#include "Resource.h"

// CMyShowMsg �Ի���

class CMyShowMsg : public CDialog
{
	DECLARE_DYNAMIC(CMyShowMsg)

public:
	CMyShowMsg(CWnd* pParent = NULL);   // ��׼���캯��
	CMyShowMsg(LPCTSTR msg);
	virtual ~CMyShowMsg();

	enum { IDD = IDD_DIALOG_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString text;
	virtual BOOL OnInitDialog();
};
