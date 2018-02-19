// DLTSguiView.h : interface of the CDLTSguiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLTSGUIVIEW_H__62A95714_1D3E_4078_B140_31E5022C2E14__INCLUDED_)
#define AFX_DLTSGUIVIEW_H__62A95714_1D3E_4078_B140_31E5022C2E14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDLTSguiDoc;
class CDataElement;
class CDataArray;




class CDLTSguiView : public CView
{
protected: // create from serialization only
	CDLTSguiView();
	DECLARE_DYNCREATE(CDLTSguiView)

// Attributes
public:
	CDLTSguiDoc* GetDocument();
	double m_maxX;
	double m_minX;
	double m_maxY;
	double m_minY;
// Operations
public:


	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLTSguiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnFileImport();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawScaleXTrans(CDC* pDC, double value, CRect & rect, COLORREF lineColor);
	void DrawScaleYTrans(CDC* pDC, double value, CRect & rect, COLORREF lineColor);
	void DrawLegendTrans(CDC* pDC, CRect &rect);
	

	void DrawScaleXDlts(CDC* pDC, double value, CRect & rect, COLORREF lineColor);
	void DrawScaleYDlts(CDC* pDC, double value, CRect & rect, COLORREF lineColor);
	void DrawLegendDlts(CDC* pDC, CRect &rect);

	static DWORD WINAPI StartMeasurement(LPVOID pparam);

	//UINT CDLTSguiView::StartMeasurement2( LPVOID pParam );

	virtual ~CDLTSguiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bShowTransient;
	bool m_bShowDltsDiagram;
	

// Generated message map functions
protected:
	void CalculateDrawRect(CDC* pDC, CRect &rect);
	BOOL ShowProperties();
	void CalculateDiagramRange(CDataArray *dataArray);


	bool bValidRange;
	CPoint ScalePointTrans(double x, double y, CRect drawRect);
	void DrawGridTrans(CDC* pDC, CRect &rect);
	void DrawGraphTrans(CDC* pDC, CRect &rect);


	CPoint ScalePointDlts(double x, double y, CRect drawRect);
	void DrawGridDlts(CDC* pDC, CRect &rect);
	void DrawGraphDlts(CDC* pDC, CRect &rect);

	//{{AFX_MSG(CDLTSguiView)
	afx_msg void OnFileStartCt();
	afx_msg void OnUpdateMenuFile(CCmdUI* pCmdUI);
	afx_msg void OnFileStartCu();
	afx_msg void OnFileStopMeasurement();
	afx_msg void OnUpdateFileStopMeasurement(CCmdUI* pCmdUI);
	afx_msg void OnGraphProperties();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVisibleAreaReset();
	afx_msg void OnWriteVoltage();
	afx_msg void OnEditProperties();
	afx_msg void OnEditBoontonZero();
	afx_msg void OnGraphCt();
	afx_msg void OnUpdateGraphCt(CCmdUI* pCmdUI);
	afx_msg void OnGraphDlts();
	afx_msg void OnUpdateGraphDlts(CCmdUI* pCmdUI);
	afx_msg void OnGraphDoubleBc();
	afx_msg void OnUpdateGraphDoubleBc(CCmdUI* pCmdUI);
	afx_msg void OnGraphLokin();
	afx_msg void OnUpdateGraphLokin(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DLTSguiView.cpp
inline CDLTSguiDoc* CDLTSguiView::GetDocument()
   { return (CDLTSguiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLTSGUIVIEW_H__62A95714_1D3E_4078_B140_31E5022C2E14__INCLUDED_)
