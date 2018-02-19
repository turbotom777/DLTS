// Paramaters.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "PropertyDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamaters dialog


CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertyDlg)
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
	m_tempDeviance = 0.0f;
	//}}AFX_DATA_INIT
	m_bEnable = true;
}


void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDlg)
	DDX_Text(pDX, IDC_EDIT_NUM_AVERAGING, m_numAveraging);
	DDV_MinMaxInt(pDX, m_numAveraging, 1, 300);
	DDX_Text(pDX, IDC_EDIT_PULSE_VOLTAGE, m_pulseVoltage);
	DDV_MinMaxFloat(pDX, m_pulseVoltage, -5.f, 5.f);
	DDX_Text(pDX, IDC_EDIT_PULSE_WIDTH, m_pulseWidth);
	DDV_MinMaxInt(pDX, m_pulseWidth, 100, 10000);
	DDX_Text(pDX, IDC_EDIT_REVERSE_VOLTAGE, m_reverseVoltage);
	DDV_MinMaxFloat(pDX, m_reverseVoltage, -10.f, 5.f);
	DDX_Text(pDX, IDC_EDIT_T1, m_t1);
	DDX_Text(pDX, IDC_EDIT_T2, m_t2);
	DDX_Text(pDX, IDC_EDIT_TEMP_END, m_tempEnd);
	DDX_Text(pDX, IDC_EDIT_TEMP_START, m_tempStart);
	DDX_Text(pDX, IDC_EDIT_TEMP_STEP, m_tempStep);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_gain);
	DDV_MinMaxInt(pDX, m_gain, 1, 500);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_delay);
	DDV_MinMaxInt(pDX, m_delay, 10, 5000);
	DDX_Check(pDX, IDC_CHECK_SINGLE_TEMP, m_singleTemperature);
	DDX_Radio(pDX, IDC_RADIO_RANGE_2, m_radioNb);
	DDX_Text(pDX, IDC_EDIT_TEMP_DEVIANCE, m_tempDeviance);
	DDV_MinMaxFloat(pDX, m_tempDeviance, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertyDlg)
	ON_BN_CLICKED(IDC_CHECK_SINGLE_TEMP, OnCheckSingleTemp)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamaters message handlers

void CPropertyDlg::OnCheckSingleTemp() 
{
	EnableDlgItems();
}

int CPropertyDlg::DoModal() 
{
	int val = CDialog::DoModal();

	m_rangeMultiplier =  (int) pow(10.0, m_radioNb);
	return val;
}

void CPropertyDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
	m_radioNb = (int) log10((float)m_rangeMultiplier);
	UpdateData(FALSE);
	EnableDlgItems();
}


void CPropertyDlg::EnableDlgItems()
{
		
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_TEMP_START)->EnableWindow(!m_singleTemperature && m_bEnable);
	GetDlgItem(IDC_EDIT_TEMP_END)->EnableWindow(!m_singleTemperature && m_bEnable);
	GetDlgItem(IDC_EDIT_TEMP_STEP)->EnableWindow(!m_singleTemperature && m_bEnable);	
	GetDlgItem(IDC_EDIT_NUM_AVERAGING)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_PULSE_VOLTAGE)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_PULSE_WIDTH)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_REVERSE_VOLTAGE)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_GAIN)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_CHECK_SINGLE_TEMP)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_RADIO_RANGE_2)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_RADIO_RANGE_20)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_RADIO_RANGE_200)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_RADIO_RANGE_2000)->EnableWindow(m_bEnable);
	GetDlgItem(IDC_EDIT_TEMP_DEVIANCE)->EnableWindow(m_bEnable);

}
