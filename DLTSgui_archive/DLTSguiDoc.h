// DLTSguiDoc.h : interface of the CDLTSguiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLTSGUIDOC_H__D8B7065C_A73E_428F_88E4_B127BB2C8611__INCLUDED_)
#define AFX_DLTSGUIDOC_H__D8B7065C_A73E_428F_88E4_B127BB2C8611__INCLUDED_

#include "DLTSguiView.h"	// Added by ClassView
#include "DataArray.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataArrayList;
//class CWorkspaceWnd;

class CDLTSdevice;

class CDLTSguiDoc : public CDocument
{
protected: // create from serialization only
	CDLTSguiDoc();
	DECLARE_DYNCREATE(CDLTSguiDoc)

// Attributes
public:
	double m_ctMaxX;
	double m_ctMaxY;
	double m_ctMinX;
	double m_ctMinY;


	int m_t1;
	int m_t2;

	int m_pulseWidth;
	int m_delay;
	int m_numberOfAveraging;
	int m_gain;
	float m_reverseVoltage;
	float m_pulseVoltage;
	float m_tempStart;
	float m_tempEnd;
	float m_tempStep;
	bool m_bSingleTemp;

	CDataArray *m_pSelectedDataArray;
// Operations
public:


	void setPulseWidth(int pulseWidth);
	void setDelay(int delay);
	void setNumberOfAveragings(int numberOfAveraging);
	void setGain(int gain);
	void setReverseVoltage(float pulseWidth);
	void setPulseVoltage(float pulseVoltage);
	void setStartTemp(float tempStart);
	void setEndTemp(float tempEnd);
	void setTempStep(float tempStep);
	void setSingleTemperature(bool bSingleTemp);


	int getPulseWidth();
	int getDelay();
	int getNumberOfAveragings();
	int getGain();
	float getReverseVoltage();
	float getPulseVoltage();
	float getStartTemp();
	float getEndTemp();
	float getTempStep();
	bool isSingleTemperature();

	float getNextTemperature(float Tsetpoint);
	bool reachedEndTemperature(float Tcurrent);




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLTSguiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void OnGraphProperties();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	double Lokin(CDataArray *dataArray);
	void setTempDeviance(float deviance);
	float getTempDeviance();
	double DoubleBoxCar(CDataArray *dataArray);
	bool getSingleTemperature();
	CDLTSguiView* GetCurrentView();
	CDataArrayList *GetDataArrayList();
	void ImportFile(CStdioFile & file);


	virtual ~CDLTSguiDoc();

	void UpdateAllViews();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double parseNumber(CString strNumber);

	CDataArrayList *m_dataArrayList;


// Generated message map functions
protected:
	float m_tempDeviance;

//	CWorkspaceWnd * GetWorkspaceWnd();
	
	//{{AFX_MSG(CDLTSguiDoc)
	afx_msg void OnVisibleAreaResetAll();
	afx_msg void OnUpdateFileImport(CCmdUI* pCmdUI);
	afx_msg void OnFileExportStatistic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLTSGUIDOC_H__D8B7065C_A73E_428F_88E4_B127BB2C8611__INCLUDED_)
