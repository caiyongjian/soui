#include "StdAfx.h"
#include "ImageMergerHandler.h"
#include "droptarget.h"

CImageMergerHandler::CImageMergerHandler(void):m_pPageRoot(NULL),m_pImgCanvas(NULL)
{
}

CImageMergerHandler::~CImageMergerHandler(void)
{
}

void CImageMergerHandler::OnFileDropdown( HDROP hdrop )
{
    bool success = false;
    WCHAR filename[MAX_PATH];
    UINT files = DragQueryFile(hdrop,-1,NULL,0);
    for(UINT i=0;i<files;i++)
    {
        success=!!DragQueryFileW(hdrop, i, filename, MAX_PATH);
        if(success)
        {
            AddFile(filename);
        }
    }

}

void CImageMergerHandler::OnInit(SWindow *pRoot)
{
    m_pPageRoot = pRoot->FindChildByName(L"page_imagemerge");
    m_pImgCanvas = m_pPageRoot->FindChildByName2<SImgCanvas>(L"wnd_canvas");//CDropTarget_Canvas
    IDropTarget *pDT = new CDropTarget(this);
    pRoot->GetContainer()->RegisterDragDrop(m_pImgCanvas->GetSwnd(),pDT);
    pDT->Release();
}

void CImageMergerHandler::AddFile(LPCWSTR pszFileName)
{
    m_pImgCanvas->AddFile(pszFileName);
}

void CImageMergerHandler::OnSave()
{
    CFileDialogEx dlgSave(FALSE,_T("png"),0,6,_T("png files(*.png)\0*.png\0All files (*.*)\0*.*\0\0"));
    if(dlgSave.DoModal()==IDOK)
    {
        m_pImgCanvas->Save2File(S_CT2W(dlgSave.m_szFileName));
    }
}

void CImageMergerHandler::OnClear()
{
    m_pImgCanvas->Clear();
}

void CImageMergerHandler::OnModeHorz()
{
    if(!m_pImgCanvas) return;
    m_pImgCanvas->SetVertical(FALSE);
}

void CImageMergerHandler::OnModeVert()
{
    if(!m_pImgCanvas) return;
    m_pImgCanvas->SetVertical(TRUE);
}

