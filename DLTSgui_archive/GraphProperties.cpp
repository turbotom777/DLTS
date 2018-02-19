// GraphProperties.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "GraphProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties dialog


CGraphProperties::CGraphProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphProperties)
	m_maxX = 0;
	m_maxY = 0;
	m_minX = 0;
	m_minY = 0;
	//}}AFX_DATA_INIT
}


void CGraphProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphProperties)
	DDX_Text(pDX, IDC_MAX_X, m_maxX);
	DDV_MinMaxDouble(pDX, m_maxX, 1., 20.);
	DDX_Text(pDX, IDC_MAX_Y, m_maxY);
	DDX_Text(pDX, IDC_MIN_X, m_minX);
	DDV_MinMaxDouble(pDX, m_minX, 0., 19.);
	DDX_Text(pDX, IDC_MIN_Y, m_minY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphProperties, CDialog)
	//{{AFX_MSG_MAP(CGraphProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties message handlers
