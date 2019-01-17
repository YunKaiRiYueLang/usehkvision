#pragma once

#include "stdafx.h"
#include "Resource.h"

// CMyShowMsg 对话框

class CMyShowMsg : public CDialog
{
	DECLARE_DYNAMIC(CMyShowMsg)

public:
	CMyShowMsg(CWnd* pParent = NULL);   // 标准构造函数
	CMyShowMsg(LPCTSTR msg);
	virtual ~CMyShowMsg();

	enum { IDD = IDD_DIALOG_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString text;
	virtual BOOL OnInitDialog();
};
