// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "DLTSgui.h"

#include "ChildFrm.h"
#include "WorkspaceWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	m_pWorkspaceWnd = new CWorkspaceWnd();
}

CChildFrame::~CChildFrame()
{
	m_pWorkspaceWnd->DestroyWindow();
	delete m_pWorkspaceWnd;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	if (!m_pWorkspaceWnd->Create("", this, CSize(200, 300), TRUE, IDC_DOCKINGBAR)){       
		TRACE0("Failed to create Docking bar\n");    
		return false;
	}

	EnableDocking(CBRS_ALIGN_ANY);

	m_pWorkspaceWnd->SetBarStyle(m_pWorkspaceWnd->GetBarStyle() |               
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_LEFT );

	m_pWorkspaceWnd->EnableDocking(CBRS_ALIGN_LEFT);
	
	DockControlBar(m_pWorkspaceWnd, AFX_IDW_DOCKBAR_LEFT);
	


	SetIcon(AfxGetApp()->LoadIcon(IDI_DLTS_ICON), TRUE);

	return 0;
}

void CChildFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CMDIChildWnd::OnShowWindow(bShow, nStatus);	
	this->MDIMaximize();
	
}
