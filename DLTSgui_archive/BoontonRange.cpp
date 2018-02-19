// BoontonRange.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "BoontonRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoontonRange dialog


CBoontonRange::CBoontonRange(CWnd* pParent /*=NULL*/)
	: CDialog(CBoontonRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoontonRange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_range = 0;
}


void CBoontonRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoontonRange)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBoontonRange, CDialog)
	//{{AFX_MSG_MAP(CBoontonRange)
	ON_BN_CLICKED(IDC_RADIO_RANGE_2, OnRadioRange2pF)
	ON_BN_CLICKED(IDC_RADIO_RANGE_20, OnRadioRange20pF)
	ON_BN_CLICKED(IDC_RADIO_RANGE_200, OnRadioRange200pF)
	ON_BN_CLICKED(IDC_RADIO_RANGE_2000, OnRadioRange2000pF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoontonRange message handlers


void CBoontonRange::setRange(int range){
	m_range = range;
}
int CBoontonRange::getRange(){
	return m_range;
}

void CBoontonRange::OnRadioRange2pF() 
{
	m_range = 1;
}

void CBoontonRange::OnRadioRange20pF() 
{
	m_range =10;
}

void CBoontonRange::OnRadioRange200pF() 
{
	m_range = 100;
}

void CBoontonRange::OnRadioRange2000pF() 
{
	m_range = 1000;
}
