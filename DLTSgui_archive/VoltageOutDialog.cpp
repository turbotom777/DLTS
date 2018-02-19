// VoltageOutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "VoltageOutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoltageOutDialog dialog


CVoltageOutDialog::CVoltageOutDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CVoltageOutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoltageOutDialog)
	m_voltageOut = 0.0f;
	//}}AFX_DATA_INIT
}


void CVoltageOutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoltageOutDialog)
	DDX_Text(pDX, IDC_EDIT_VOTAGE_OUT, m_voltageOut);
	DDV_MinMaxFloat(pDX, m_voltageOut, -6.f, 6.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVoltageOutDialog, CDialog)
	//{{AFX_MSG_MAP(CVoltageOutDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoltageOutDialog message handlers
