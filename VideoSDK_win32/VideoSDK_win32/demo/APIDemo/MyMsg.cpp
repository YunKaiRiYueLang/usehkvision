#include "stdafx.h"
#include "MyMsg.h"


CMyMsg::CMyMsg(void)
: m_hHwnd(NULL)
, m_nMsg(0)
, bIsExit(FALSE)
{

}


CMyMsg::CMyMsg(HWND h, void* lParam, UINT nMsg)
: m_hHwnd(NULL)
, m_nMsg(0)
, bIsExit(FALSE)
{
	m_hHwnd = h;
	m_ctrl = lParam;
	m_nMsg = nMsg;
}


CMyMsg::~CMyMsg(void)
{
 
}


void CMyMsg::SetParam(HWND h, void* lParam, UINT nMsg)
{
	m_hHwnd = h;
	m_ctrl = lParam;
	m_nMsg = nMsg;
}


void CMyMsg::Msg(char *Type, char *msg)
{
	if (bIsExit)
	{
		return;
	}

	int i = 0;
	int len = (int)strlen(msg) + 1;

	char *LPmsg = new char[len];
	memset(LPmsg, 0, len);

	while (LPmsg[i] = msg[i++]);

	::PostMessage(m_hHwnd, m_nMsg, (WPARAM)Type, (LPARAM)LPmsg);
}


void CMyMsg::Msg(char *Type,CString& msg)
{
	if (bIsExit)
	{
		return;
	}

	csmsg.Lock();

	int len = msg.GetLength() + 1;
	char *LPmsg = new char[len];

	memset(LPmsg, 0, len);
	strcpy_s(LPmsg, len, msg.GetBuffer());

	::PostMessage(m_hHwnd, m_nMsg, (WPARAM)Type, (LPARAM)LPmsg);

	csmsg.Unlock();
}

//
//void CMyMsg::Msg(char *Type, ListData* msg)
//{
//	if (bIsExit)
//	{
//		return;
//	}
// 
//	csmsg.Lock();
//	::PostMessage(m_hHwnd, m_nMsg, (WPARAM)Type, (LPARAM)msg);
//	csmsg.Unlock();
//}


LRESULT CMyMsg::OnMymsg(WPARAM wParam, LPARAM lParam)
{
	CString type = (char*)wParam;

	char *msg = (char*)lParam;

	if (type == "CListBox")
	{
		CListBox *listbox = (CListBox*)m_ctrl;

		int cnt = listbox->GetCount();
		listbox->InsertString(cnt, msg);
		listbox->SetCurSel(cnt);

		delete msg;
	}
	else if (type == "CListCtrl")
	{
		CListCtrl *listctrl = (CListCtrl*)m_ctrl;

		int cnt = listctrl->GetItemCount();
		if (cnt > 200)
		{
			listctrl->DeleteAllItems();
		}
 
		listctrl->InsertItem(0, type);
		listctrl->SetItemText(0, 1, msg);
		 
		delete msg;
	}
	else if (type == "Result")
	{
		CListCtrl *listctrl = (CListCtrl*)m_ctrl;
		
		int cnt = listctrl->GetItemCount();
		if (cnt > 200)
		{
			listctrl->DeleteAllItems();
		}

		return 0;
	}

	return 0;
}