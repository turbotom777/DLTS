// Console.cpp: implementation of the CConsole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dltsgui.h"
#include "Console.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConsole::CConsole()
{
	m_edit = new CRichEditCtrl();
}

CConsole::~CConsole()
{
	if (m_edit != NULL){
		delete m_edit;
		m_edit = NULL;
	}
}


BEGIN_MESSAGE_MAP(CConsole, CSizingControlBar)
    //{{AFX_MSG_MAP(CConsole)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CConsole::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rRect;
	GetClientRect(rRect);
	m_edit->Create(WS_BORDER | WS_CHILD | WS_VISIBLE |WS_VSCROLL | WS_HSCROLL |ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY , rRect, this, IDC_CONSOLE_EDIT);
	return 0;
}

void CConsole::OnDestroy() 
{
	m_edit->DestroyWindow();
	CSizingControlBar::OnDestroy();	
}

void CConsole::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CSizingControlBar::OnShowWindow(bShow, nStatus);
	m_edit->ShowWindow(SW_SHOW);
	m_edit->EnableWindow(TRUE);	
}

void CConsole::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBar::OnSize(nType, cx, cy);
	CRect rRect;
	GetClientRect(rRect);
	m_edit->MoveWindow(rRect);
	
}

void CConsole::AddText(CString text, bool bScroll)
{
	if (m_edit == NULL){
		return;
	}
	m_edit->SetSel(m_edit->GetTextLength(), (-1));
	m_edit->ReplaceSel(text);
	if (bScroll){
		m_edit->LineScroll(1);
	}
}
