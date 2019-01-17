#include "resource.h"		// main symbols

#include "APIDemoDlg.h"



extern CAPIDemoDlg * g_pMainDlg;
//extern CSubDlgLocalRec * g_SubDlg;

class CAPIDemoApp : public CWinApp
{
public:
	CAPIDemoApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
