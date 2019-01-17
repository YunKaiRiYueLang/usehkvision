

#pragma once
#include "targetver.h"
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include "../include/VideoSDK.h"
#pragma comment(lib, "../include/VideoSDK.lib")
enum CallType
{
	UnDef,
	RealPlay,
	LocalPlay,
	RemotePlay
};


typedef struct _USERDATA
{
	CallType ctype;
	char msg[1024];

}USERDATA, *PUSERDATA;


typedef struct _CallBackParam
{
	int i;
	int j;
}CALLBACKPARAM;

#define CALLBACKMSG (WM_USER + 0x100)
#define SHOWMSG (WM_USER + 0x101)