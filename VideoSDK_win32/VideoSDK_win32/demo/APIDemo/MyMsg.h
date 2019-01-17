#pragma once
#ifdef DLLEXPORT
#define MY_MFC_MyMsg __declspec( dllexport )
#else
#define MY_MFC_MyMsg __declspec( dllimport )
#endif //DLLEXPORT

#include <afxmt.h>

class /*MY_MFC_MyMsg*/ CMyMsg
{
public:
	CMyMsg(void);
	CMyMsg(HWND h, void* lParam, UINT nMsg);
	virtual ~CMyMsg(void);
	BOOL bIsExit;
	CCriticalSection csmsg;
private:
	HWND m_hHwnd;
	UINT m_nMsg;
	void *m_ctrl;

public:
	void Msg(char *Type, char *msg);
	void Msg(char *Type, CString& msg);
	void SetParam(HWND h, void* lParam, UINT nMsg);
	LRESULT OnMymsg(WPARAM wParam, LPARAM lParam);
};



