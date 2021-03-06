// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"

#include <time.h>
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited=FALSE;
} 

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

void CMainDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	if(bShow)
	{
 		AnimateHostWindow(200,AW_CENTER);
	}
}

struct flashtime{
    int timeEnd;
    wchar_t szFlash[50];
}g_flashs[]=
{
    {0, L"morning.swf"},
    {8,L"noon.swf"},
    {12,L"afternoon.swf"},
    {18,L"night.swf"}
};

BOOL CMainDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    m_bLayoutInited=TRUE;
    SFlashCtrl * pFlash = FindChildByName2<SFlashCtrl>(L"flash_bkgnd");
    if(pFlash)
    {
        wchar_t szCurDir[MAX_PATH+1];
        GetCurrentDirectoryW(MAX_PATH,szCurDir);

        time_t long_time;
        time( &long_time );
        struct tm * t=localtime(&long_time);

        wchar_t szFlash[MAX_PATH];
        for(int i=3;i>=0;i--)
        {
            if(t->tm_hour>=g_flashs[i].timeEnd)
            {
                swprintf(szFlash,L"%s\\flash\\%s",szCurDir,g_flashs[i].szFlash);
                break;
            }
        }

        pFlash->Play(szFlash);
    }
    return 0;
}

void CMainDlg::OnBtnSetting()
{
    STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
    if(pTab)
    {
        STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
        if(pTurn3d)
        {
            pTurn3d->Turn(pTab->GetPage(_T("login")),pTab->GetPage(_T("settings")),FALSE);
        }
    }
}

void CMainDlg::OnBtnSettingOK()
{
    STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
    if(pTab)
    {
        STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
        if(pTurn3d)
        {
            pTurn3d->Turn(pTab->GetPage(_T("settings")),pTab->GetPage(_T("login")),TRUE);
        }
    }
}

void CMainDlg::OnBtnSettingCancel()
{
    STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
    if(pTab)
    {
        STurn3dView * pTurn3d = FindChildByName2<STurn3dView>(L"turn3d");
        if(pTurn3d)
        {
            pTurn3d->Turn(pTab->GetPage(_T("settings")),pTab->GetPage(_T("login")),TRUE);
        }
    }
}

BOOL CMainDlg::OnTurn3D( EventArgs *pEvt )
{
    EventTurn3d *pEvt3dTurn = (EventTurn3d*)pEvt;
    STabCtrl *pTab= FindChildByName2<STabCtrl>(L"tab_main");
    if(pEvt3dTurn->bTurn2Front_)
    {
        pTab->SetCurSel(_T("login"));
    }else
    {
        pTab->SetCurSel(_T("settings"));
    }
    return TRUE;
}
