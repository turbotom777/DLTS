// Paramaters.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "Parameters.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamaters dialog


CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	m_numAveraging = 1;
	m_pulseVoltage = -1.0f;
	m_pulseWidth = 500;
	m_reverseVoltage = -6.0f;
	m_t1 = 100;
	m_t2 = 1000;
	m_tempEnd = 0.0f;
	m_tempStart = 0.0f;
	m_tempStep = 1.0f;
	m_gain = 1;
	m_delay = 20;
	m_singleTemperature = FALSE;
	m_radioNb = -1;
	m_deviance = 0.0f;
	//}}AFX_DATA_INIT
}


void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Text(pDX, IDC_EDIT_NUM_AVERAGING, m_numAveraging);
	DDV_MinMaxInt(pDX, m_numAveraging, 1, 20);
	DDX_Text(pDX, IDC_EDIT_PULSE_VOLTAGE, m_pulseVoltage);
	DDV_MinMaxFloat(pDX, m_pulseVoltage, -5.f, 5.f);
	DDX_Text(pDX, IDC_EDIT_PULSE_WIDTH, m_pulseWidth);
	DDV_MinMaxInt(pDX, m_pulseWidth, 300, 10000);
	DDX_Text(pDX, IDC_EDIT_REVERSE_VOLTAGE, m_reverseVoltage);
	DDV_MinMaxFloat(pDX, m_reverseVoltage, -10.f, 5.f);
	DDX_Text(pDX, IDC_EDIT_T1, m_t1);
	DDV_MinMaxInt(pDX, m_t1, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_T2, m_t2);
	DDV_MinMaxInt(pDX, m_t2, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_TEMP_END, m_tempEnd);
	DDX_Text(pDX, IDC_EDIT_TEMP_START, m_tempStart);
	DDX_Text(pDX, IDC_EDIT_TEMP_STEP, m_tempStep);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_gain);
	DDV_MinMaxInt(pDX, m_gain, 1, 500);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_delay);
	DDV_MinMaxInt(pDX, m_delay, 100, 5000);
	DDX_Check(pDX, IDC_CHECK_SINGLE_TEMP, m_singleTemperature);
	DDX_Radio(pDX, IDC_RADIO_RANGE_2, m_radioNb);
	DDX_Text(pDX, IDC_EDIT_TEMP_DEVIANCE, m_deviance);
	DDV_MinMaxFloat(pDX, m_deviance, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_BN_CLICKED(IDC_CHECK_SINGLE_TEMP, OnCheckSingleTemp)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamaters message handlers

void CParameters::OnCheckSingleTemp() 
{
	UpdateData(TRUE);	
	GetDlgItem(IDC_EDIT_TEMP_START)->EnableWindow(!m_singleTemperature);
	GetDlgItem(IDC_EDIT_TEMP_END)->EnableWindow(!m_singleTemperature);
	GetDlgItem(IDC_EDIT_TEMP_STEP)->EnableWindow(!m_singleTemperature);	
}

int CParameters::DoModal() 
{
	int val = CDialog::DoModal();

	m_rangeMultiplier =  (int) pow(10.0, m_radioNb);
	return val;
}

void CParameters::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
	m_radioNb = (int) log10((float)m_rangeMultiplier);
	UpdateData(FALSE);
	OnCheckSingleTemp();
	
}

