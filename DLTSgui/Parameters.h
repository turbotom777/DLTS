#if !defined(AFX_PARAMATERS_H__DF367098_C510_4567_B112_026C305DC673__INCLUDED_)
#define AFX_PARAMATERS_H__DF367098_C510_4567_B112_026C305DC673__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Paramaters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamaters dialog

class CParameters : public CDialog
{
// Construction
public:
	CParameters(CWnd* pParent = NULL);   // standard constructor

	int m_rangeMultiplier;

// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_PARAMETER_DIALOG };
	int		m_numAveraging;
	float	m_pulseVoltage;
	int		m_pulseWidth;
	float	m_reverseVoltage;
	int		m_t1;
	int		m_t2;
	float	m_tempEnd;
	float	m_tempStart;
	float	m_tempStep;
	int		m_gain;
	int		m_delay;
	BOOL	m_singleTemperature;
	int		m_radioNb;
	float	m_deviance;
	int		m_recordingTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameters)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	afx_msg void OnCheckSingleTemp();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMATERS_H__DF367098_C510_4567_B112_026C305DC673__INCLUDED_)
