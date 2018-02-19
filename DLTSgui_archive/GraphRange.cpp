// GraphRange.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "GraphRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphRange dialog


CGraphRange::CGraphRange(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphRange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraphRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphRange)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphRange, CDialog)
	//{{AFX_MSG_MAP(CGraphRange)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphRange message handlers
