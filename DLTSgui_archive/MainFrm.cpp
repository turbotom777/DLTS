// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DLTSgui.h"

#include "MainFrm.h"
#include "WorkspaceWnd.h"
#include "Console.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROJECT_VIEW, OnUpdateViewDockingBar)
	ON_COMMAND(ID_VIEW_PROJECT_VIEW, OnViewDockingBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ACTION_BAR, OnUpdateViewActionBar)
	ON_COMMAND(ID_VIEW_ACTION_BAR, OnViewActionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONSOLE_BAR, OnUpdateViewConsoleBar)
	ON_COMMAND(ID_VIEW_CONSOLE_BAR, OnViewConsoleBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	//m_pWorkspaceWnd = new CWorkspaceWnd();
	m_pConsole = new CConsole();

}

CMainFrame::~CMainFrame()
{
	//m_pWorkspaceWnd->DestroyWindow();
	m_pConsole->DestroyWindow();
	//delete m_pWorkspaceWnd;
	delete m_pConsole;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	if (!m_wndActionBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndActionBar.LoadToolBar(IDR_TOOLBAR_ACTION))
	{
		TRACE0("Failed to create actionbar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndActionBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndActionBar);

/*
	if (!m_pWorkspaceWnd->Create("", this, CSize(200, 300), TRUE, IDC_DOCKINGBAR)){       
		TRACE0("Failed to create Docking bar\n");    
		return false;      // fail to create
	}
	*/


	if (!m_pConsole->Create("", this, CSize(300, 100), TRUE, IDC_CONSOLEBAR)){       
		TRACE0("Failed to create Docking bar\n");    
		return false;      // fail to create
	}

	/*
	m_pWorkspaceWnd->SetBarStyle(m_pWorkspaceWnd->GetBarStyle() |               
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER);

  */
	m_pConsole->SetBarStyle(m_pConsole->GetBarStyle() |               
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER);

//	m_pWorkspaceWnd->EnableDocking(CBRS_ALIGN_ANY);
	m_pConsole->EnableDocking(CBRS_ALIGN_ANY);

//	m_pWorkspaceWnd->SetWindowText("Articles");
//	DockControlBar(m_pWorkspaceWnd, AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(m_pConsole, AFX_IDW_DOCKBAR_BOTTOM);

	
    SetIcon(AfxGetApp()->LoadIcon(IDI_DLTS_ICON), TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnUpdateViewDockingBar(CCmdUI* pCmdUI) 
{
    //pCmdUI->SetCheck((m_pWorkspaceWnd->GetStyle() & WS_VISIBLE)!=0);
}

void CMainFrame::OnViewDockingBar() 
{
	/*
	if (m_pWorkspaceWnd->GetStyle() & WS_VISIBLE)
    {
		 ShowControlBar(m_pWorkspaceWnd, FALSE, FALSE);
    }
    else
    {
        ShowControlBar(m_pWorkspaceWnd, TRUE, FALSE);
		m_pWorkspaceWnd->UpdateCurrentView();
    }
	*/
}


void CMainFrame::OnUpdateViewActionBar(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck((m_wndActionBar.GetStyle() & WS_VISIBLE)!=0);
}

void CMainFrame::OnViewActionBar() 
{
	if (m_wndActionBar.GetStyle() & WS_VISIBLE)
    {
		 ShowControlBar(&m_wndActionBar, FALSE, FALSE);
    }
    else
    {
        ShowControlBar(&m_wndActionBar, TRUE, FALSE);
    }
}

void CMainFrame::OnUpdateViewConsoleBar(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck((m_pConsole->GetStyle() & WS_VISIBLE)!=0);
}

void CMainFrame::OnViewConsoleBar() 
{
	if (m_pConsole->GetStyle() & WS_VISIBLE)
    {
		 ShowControlBar(m_pConsole, FALSE, FALSE);
    }
    else
    {
        ShowControlBar(m_pConsole, TRUE, FALSE);
    }
}

/*
CWorkspaceWnd* CMainFrame::GetWorkspaceWnd(){
	return m_pWorkspaceWnd;
}
*/

CConsole* CMainFrame::GetConsole(){
	return m_pConsole;
}

BOOL CMainFrame::DestroyWindow() 
{
	WINDOWPLACEMENT wndPlacement;
	GetWindowPlacement( &wndPlacement);
	CWinApp * pApp = AfxGetApp();

	pApp->WriteProfileInt("Main Window","Top",wndPlacement.rcNormalPosition.top);
	pApp->WriteProfileInt("Main Window","Left",wndPlacement.rcNormalPosition.left);
	pApp->WriteProfileInt("Main Window","Bottom",wndPlacement.rcNormalPosition.bottom);
	pApp->WriteProfileInt("Main Window","Right",wndPlacement.rcNormalPosition.right);
	pApp->WriteProfileInt("Main Window","showCmd",wndPlacement.showCmd);
	pApp->WriteProfileInt("Main Window","valid",TRUE);
	
	return CMDIFrameWnd::DestroyWindow();
}

