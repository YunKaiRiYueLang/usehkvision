// MyShowMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "APIDemo.h"
#include "MyShowMsg.h"


// CMyShowMsg 对话框

IMPLEMENT_DYNAMIC(CMyShowMsg, CDialog)

CMyShowMsg::CMyShowMsg(CWnd* pParent /*=NULL*/)
: CDialog(CMyShowMsg::IDD, pParent)
{

}


CMyShowMsg::CMyShowMsg(LPCTSTR msg)
: CDialog(CMyShowMsg::IDD, NULL)
, text(msg)
{

}


CMyShowMsg::~CMyShowMsg()
{
}

void CMyShowMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyShowMsg, CDialog)
 
END_MESSAGE_MAP()


// CMyShowMsg 消息处理程序


 

BOOL CMyShowMsg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//CString text;

	//text.Format("hello\r\n你是谁？\n消息处理程序\r\n");
	text.Replace("> <", ">\r\n<");

	SetDlgItemText(IDC_EDIT1, text.GetBuffer());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
