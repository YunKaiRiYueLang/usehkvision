// MyShowMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "APIDemo.h"
#include "MyShowMsg.h"


// CMyShowMsg �Ի���

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


// CMyShowMsg ��Ϣ�������


 

BOOL CMyShowMsg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//CString text;

	//text.Format("hello\r\n����˭��\n��Ϣ�������\r\n");
	text.Replace("> <", ">\r\n<");

	SetDlgItemText(IDC_EDIT1, text.GetBuffer());

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
