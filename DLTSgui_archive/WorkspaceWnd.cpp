#include "stdafx.h"
#include "WorkspaceWnd.h"
#include "MainFrm.h"
#include "DataArray.h"
#include "DLTSguiDoc.h"
#include "DataArrayList.h"
#include "ListFrame.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TAB_CT 0
#define TAB_CU 1


/////////////////////////////////////////////////////////////////////////////

CWorkspaceWnd::CWorkspaceWnd()
{
    m_pTabCtrl  = new CTabCtrl();
	m_pListFrame = new CListFrame();

    m_bIsBarActive = false;
}

CWorkspaceWnd::~CWorkspaceWnd()
{
    if (m_pTabCtrl != NULL) {
        delete m_pTabCtrl;
    }

    if (m_pListFrame != NULL) {
        delete m_pListFrame;
    }
}


BEGIN_MESSAGE_MAP(CWorkspaceWnd, baseCDockingBar)
    //{{AFX_MSG_MAP(CWorkspaceWnd)
    ON_WM_CREATE()
    ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_DOCKING_TAB, OnSelchangeTab)
    ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockingBar message handlers

int CWorkspaceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (baseCDockingBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rRect;

    GetClientRect(rRect);
	m_pTabCtrl->Create(WS_CHILD | WS_VISIBLE, rRect, this, IDC_DOCKING_TAB);
    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
    {
       if (!m_font.CreatePointFont(80, "MS Sans Serif"))
       {
           return -1;
       }
    }
  
	TCITEM tcItem0;
    tcItem0.mask = TCIF_TEXT;
    tcItem0.pszText = _T("C/t");
	int pos = m_pTabCtrl->InsertItem(TAB_CT, &tcItem0);

	/*
	TCITEM tcItem1;
    tcItem1.mask = TCIF_TEXT;
    tcItem1.pszText = _T("C/U");
	pos = m_pTabCtrl->InsertItem(TAB_CU, &tcItem1);

  */
    m_pTabCtrl->SetFont(&m_font);
	
	CRect	rect;
	GetClientRect(&rect);
	m_pListFrame->CreateEx(WS_EX_CLIENTEDGE, NULL, "", 
        WS_OVERLAPPED | WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_SORTDESCENDING | WS_TABSTOP , rRect, m_pTabCtrl, 1);


	ShowCurrentList();
    return 0;
}

void CWorkspaceWnd::OnDestroy()
{
    m_pTabCtrl->DestroyWindow();
	m_pListFrame->DestroyWindow();

    baseCDockingBar::OnDestroy();
}

void CWorkspaceWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	baseCDockingBar::OnShowWindow(bShow, nStatus);	

	m_pTabCtrl->ShowWindow(SW_SHOW);
	m_pTabCtrl->EnableWindow(TRUE);

	m_pListFrame->ShowWindow(SW_SHOW);
	m_pListFrame->EnableWindow(TRUE);

	ShowCurrentList();

}

void CWorkspaceWnd::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{

    baseCDockingBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);
    UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CWorkspaceWnd::OnSize(UINT nType, int cx, int cy) 
{
    baseCDockingBar::OnSize(nType, cx, cy);
    UpdateCurrentView();
}

void CWorkspaceWnd::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
    *pResult = 0;
	ShowCurrentList();	
}


void CWorkspaceWnd::ShowCurrentList(){
	int curSel = m_pTabCtrl->GetCurSel();
	if (curSel == TAB_CT){
		m_pListFrame->ShowWindow(SW_SHOW);
	} else if (curSel == TAB_CU){
	}	
}

void CWorkspaceWnd::ToggleStatus()
{
    m_bIsBarActive = !m_bIsBarActive;
    UpdateCurrentView();

}

void CWorkspaceWnd::UpdateCurrentView()
{
	UpdateListContent();
	CRect rc;
    GetClientRect(rc);
    m_pTabCtrl->MoveWindow(rc);

	CRect tabRect;
	m_pTabCtrl->GetItemRect(0, tabRect);
	rc.top += (tabRect.bottom - tabRect.top) + 2;
	rc.DeflateRect(2, 2);
	m_pListFrame->MoveWindow(rc);
	m_pListFrame->UpdateCurrentView();
}



void CWorkspaceWnd::UpdateListContent( )
{
	m_pListFrame->UpdateListContent();
}


void CWorkspaceWnd::SetDocument(CDLTSguiDoc *doc)
{
	m_pListFrame->m_activeDocument = doc;
}
