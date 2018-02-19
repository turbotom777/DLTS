// DLTSguiView.cpp : implementation of the CDLTSguiView class
//

#include "stdafx.h"
#include "DLTSgui.h"

#include "DLTSguiDoc.h"
#include "DLTSguiView.h"
#include "DataElement.h"
#include "DataArrayList.h"
#include "DataArray.h"
#include "math.h"
#include "graphProperties.h"
#include "VoltageOutDialog.h"
#include "PropertyDlg.h"
#include "DLTSdevice.h"
#include "Boonton7200.h"
#include "BoontonRange.h"
#include "ChildFrm.h"
#include "WorkspaceWnd.h"
#include "ListFrame.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView

IMPLEMENT_DYNCREATE(CDLTSguiView, CView)

BEGIN_MESSAGE_MAP(CDLTSguiView, CView)
	//{{AFX_MSG_MAP(CDLTSguiView)
	ON_COMMAND(ID_FILE_START_CT, OnFileStartCt)
	ON_UPDATE_COMMAND_UI(ID_FILE_START_CT, OnUpdateMenuFile)
	ON_COMMAND(ID_FILE_START_CU, OnFileStartCu)
	ON_COMMAND(ID_FILE_STOP_MEASUREMENT, OnFileStopMeasurement)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOP_MEASUREMENT, OnUpdateFileStopMeasurement)
	ON_COMMAND(ID_VISIBLE_AREA, OnGraphProperties)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_VISIBLE_AREA_RESET, OnVisibleAreaReset)
	ON_COMMAND(ID_WRITE_VOLTAGE, OnWriteVoltage)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_EDIT_BOONTON_ZERO, OnEditBoontonZero)
	ON_COMMAND(ID_GRAPH_CT, OnGraphCt)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_CT, OnUpdateGraphCt)
	ON_COMMAND(ID_GRAPH_DLTS, OnGraphDlts)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DLTS, OnUpdateGraphDlts)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_UPDATE_COMMAND_UI(ID_FILE_START_CU, OnUpdateMenuFile)
	ON_COMMAND(ID_GRAPH_DOUBLE_BC, OnGraphDoubleBc)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DOUBLE_BC, OnUpdateGraphDoubleBc)
	ON_COMMAND(ID_GRAPH_LOKIN, OnGraphLokin)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_LOKIN, OnUpdateGraphLokin)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView construction/destruction

#define BLACK RGB(0,0,0)
#define GREY RGB(220,220,220)
#define BLUE RGB(0,0,128)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)

//#define BORDER_LEFT 100
//#define BORDER_RIGHT 30
//#define BORDER_TOP 30
//#define BORDER_BOTTOM 30

#define BORDER_LEFT 0.09
#define BORDER_RIGHT 0.03
#define BORDER_TOP 0.10
#define BORDER_BOTTOM 0.10

CDLTSguiView::CDLTSguiView()
{
	bValidRange = false;

	m_maxX = 1000;
	m_maxY = 10;
	m_minX = 0;
	m_minY = 0;

	m_bShowTransient = true;
	m_bShowDltsDiagram = true;
	m_bDoubleBoxCar = true;
}

CDLTSguiView::~CDLTSguiView()
{

}

BOOL CDLTSguiView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView drawing

void CDLTSguiView::OnDraw(CDC* pDC)
{
	CDLTSguiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (GetDocument()->m_pSelectedDataArray == NULL){
		if (GetDocument()->GetDataArrayList() != NULL){
			CDataArrayList* dataArrayList = GetDocument()->GetDataArrayList();
			dataArrayList->SetFirstPosition();
			if (dataArrayList->HasNext()){
				GetDocument()->m_pSelectedDataArray = dataArrayList->GetNext();
			}
		}
	}



	if (pDC->IsPrinting()){
		int i = 0;
	}

	CRect rect;
	GetClientRect(rect);
	if ( m_bShowTransient && m_bShowDltsDiagram){
		rect.bottom = rect.top + (rect.Height()/2) ;
	}
	if (m_bShowTransient){
		this->CalculateDrawRect(pDC, rect);
		if (pDC->IsPrinting()){
			rect.bottom = rect.bottom* 8;
			rect.top = rect.top* 8;
			rect.left = rect.left* 8;
			rect.right = rect.right* 8;
		}

		this->CalculateDiagramRange(GetDocument()->m_pSelectedDataArray);
		this->DrawGridTrans(pDC, rect);
		this->DrawGraphTrans(pDC, rect);
		this->DrawLegendTrans(pDC, rect);
	}


	if ( m_bShowTransient && m_bShowDltsDiagram){
		GetClientRect(rect);
		rect.top = rect.bottom - (rect.Height()/2) ;
	}

	if (m_bShowDltsDiagram){
		this->CalculateDrawRect(pDC, rect);
		if (pDC->IsPrinting()){
			rect.bottom = rect.bottom* 8;
			rect.top = rect.top* 8;
			rect.left = rect.left* 8;
			rect.right = rect.right* 8;
		}

		this->DrawGridDlts(pDC, rect);
		this->DrawGraphDlts(pDC, rect);
		this->DrawLegendDlts(pDC, rect);
	}



}

void CDLTSguiView::CalculateDrawRect(CDC* pDC, CRect &rect)
{
	const int borderTop = rect.Height() * BORDER_TOP;
	const int borderLeft = rect.Width() * BORDER_LEFT;
	const int borderRight = rect.Width() * BORDER_RIGHT;
	const int borderBottom = rect.Height() * BORDER_BOTTOM;

//	const int borderTop =  BORDER_TOP;
//	const int borderLeft = BORDER_LEFT;
//	const int borderRight =  BORDER_RIGHT;
//	const int borderBottom =  BORDER_BOTTOM;

	CPoint pointZero;
	pointZero.x = rect.left + borderLeft;
	pointZero.y = rect.bottom - borderBottom;

	CPoint pointMax;
	pointMax.x = rect.right - borderRight;
	pointMax.y = rect.top + borderTop;

	rect.left = pointZero.x;
	rect.bottom = pointZero.y;
	rect.right = pointMax.x;
	rect.top = pointMax.y;

}



void CDLTSguiView::DrawGridTrans(CDC* pDC, CRect &rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, BLACK);
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointZero;
	pointZero.x = rect.left;
	pointZero.y = rect.bottom;

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(pointZero.x, pointZero.y);
	pDC->LineTo(pointZero.x, pointMax.y);

	pDC->MoveTo(pointZero.x, pointZero.y);
	pDC->LineTo(pointMax.x, pointZero.y);	

	const int DIVISOR_Y = 10;
	double rangeY = m_maxY - m_minY;
	double unitY = rangeY / DIVISOR_Y;
	this->DrawScaleYTrans(pDC, m_maxY, rect, GREY);
	for (int i = 0; i < DIVISOR_Y; i++){
		this->DrawScaleYTrans(pDC, m_maxY - (i*unitY), rect, GREY);
	}
	this->DrawScaleYTrans(pDC, m_minY, rect, BLACK);
	if (m_maxY > 0 && m_minY < 0){
		this->DrawScaleYTrans(pDC, 0, rect, RED);
	}



	const int DIVISOR_X = 5;
	double rangeX = m_maxX - m_minX ;
	double unitX = rangeX / DIVISOR_X;
	this->DrawScaleXTrans(pDC, m_maxX, rect, GREY);
	for (int j = 0; j < DIVISOR_X; j++){
		this->DrawScaleXTrans(pDC, m_maxX - (j*unitX), rect, GREY);
	}
	this->DrawScaleXTrans(pDC, m_minX, rect, BLACK);

	this->DrawScaleXTrans(pDC, GetDocument()->m_t1, rect, GREEN);
	this->DrawScaleXTrans(pDC, GetDocument()->m_t2, rect, GREEN);

	pDC->SelectObject(old);

	pen.DeleteObject();
	pen.DeleteObject();

}

void CDLTSguiView::DrawScaleYTrans(CDC* pDC, double value, CRect &rect, COLORREF lineColor)
{
	CString strLabel;
	strLabel.Format("%1.3f pF", value);
	CPoint scalePnt = this->ScalePointTrans(m_minX, value, rect);

	int textLength = strLabel.GetLength() * 8;
	int textHeight = 12;
	pDC->SetTextColor(BLACK);
	pDC->TextOut(scalePnt.x - textLength, scalePnt.y - (textHeight/2), strLabel);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, lineColor );
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(scalePnt.x, scalePnt.y);
	pDC->LineTo(pointMax.x, scalePnt.y);
		

	pDC->SelectObject(old);
	pen.DeleteObject();
}

void CDLTSguiView::DrawScaleXTrans(CDC *pDC, double value, CRect &rect, COLORREF lineColor)
{
	CString strLabel;
	strLabel.Format("%1.2f ms", (value / 100));
	CPoint scalePnt = this->ScalePointTrans(value, m_minY, rect);

	int textLength = strLabel.GetLength() * 8;
	int textHeight = 12;
	pDC->SetTextColor(BLACK);
	pDC->TextOut(scalePnt.x - (textLength/2), scalePnt.y + textHeight, strLabel);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, lineColor );
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(scalePnt.x, scalePnt.y);
	pDC->LineTo(scalePnt.x, pointMax.y);
		

	pDC->SelectObject(old);
	pen.DeleteObject();
}


void CDLTSguiView::DrawLegendTrans(CDC *pDC, CRect &rect)
{
	if (GetDocument()->m_pSelectedDataArray != NULL){
		CString strTemp;
		strTemp.Format("Temperature: %3.1f°C / %3.1fK", GetDocument()->m_pSelectedDataArray->GetTemperature(), (273 + GetDocument()->m_pSelectedDataArray->GetTemperature()));
		pDC->TextOut(rect.left, rect.top - 20, strTemp);

		int textLength = strTemp.GetLength() * 8;
		strTemp.Format("Reverse Voltage: %3.1fV", GetDocument()->getReverseVoltage());
		pDC->TextOut(rect.left + textLength, rect.top - 20, strTemp);

		textLength += strTemp.GetLength() * 8;
		strTemp.Format("Pulse Voltage: %3.1fV", GetDocument()->getPulseVoltage());
		pDC->TextOut(rect.left + textLength, rect.top - 20, strTemp);

		CString wndText;
		wndText.Format("%f°C", GetDocument()->m_pSelectedDataArray->GetTemperature());
		this->SetWindowText(wndText);
		UpdateData(FALSE);
	}

}


void CDLTSguiView::DrawGraphTrans(CDC* pDC, CRect &rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, BLUE);
	CPen *old = pDC->SelectObject(&pen);

	if (GetDocument()->m_pSelectedDataArray == NULL){
		return;
	}
	GetDocument()->m_pSelectedDataArray->SetFirstPosition();
	if (!GetDocument()->m_pSelectedDataArray->HasNext()){
		return;
	}
	
	bool bFirst = true;
	
	CRgn rgn;
	CPoint topLeft = rect.TopLeft();
	CPoint bottomRight = rect.BottomRight();
	rgn.CreateRectRgn(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	pDC->SelectClipRgn( & rgn);
	GetDocument()->m_pSelectedDataArray->SetFirstPosition();
	while (GetDocument()->m_pSelectedDataArray->HasNext()){
		CDataElement *element = GetDocument()->m_pSelectedDataArray->GetNext();
		CPoint drawPoint = ScalePointTrans(element->getTime(), element->getValue(), rect);
		if (bFirst){
			pDC->MoveTo(drawPoint.x, drawPoint.y);
			bFirst = false;
		} else {
			pDC->LineTo(drawPoint.x, drawPoint.y);
		}
	}
	pDC->SelectObject(old);
	pen.DeleteObject();

	CRect clientRect;
	GetClientRect(&clientRect);
	CRgn clientRgn;
	clientRgn.CreateRectRgn(clientRect.TopLeft().x, clientRect.TopLeft().y, clientRect.BottomRight().x, clientRect.BottomRight().y);
	pDC->SelectClipRgn( & clientRgn);

}


CPoint CDLTSguiView::ScalePointTrans(double x, double y, CRect drawRect)
{

	double rangeX = m_maxX - m_minX;
	double rangeY = m_maxY - m_minY;

	double unitX = (drawRect.right - drawRect.left) / rangeX;
	double unitY = (drawRect.bottom - drawRect.top) / rangeY;

	CPoint drawPoint;
	drawPoint.x = (long) ceil(x * unitX) - (long) ceil(m_minX * unitX) + drawRect.left;
	// convert rect 'normal' ko orientation.
	drawPoint.y = drawRect.bottom - ((long) ceil(y * unitY) - (long) ceil(m_minY * unitY));
	return drawPoint;
}


void CDLTSguiView::DrawGridDlts(CDC* pDC, CRect &rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, BLACK);
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointZero;
	pointZero.x = rect.left;
	pointZero.y = rect.bottom;

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(pointZero.x, pointZero.y);
	pDC->LineTo(pointZero.x, pointMax.y);

	pDC->MoveTo(pointZero.x, pointZero.y);
	pDC->LineTo(pointMax.x, pointZero.y);	

	const int DIVISOR_Y = 10;
	double rangeY = m_maxY - m_minY;
	double unitY = rangeY / DIVISOR_Y;
	this->DrawScaleYDlts(pDC, m_maxY, rect, GREY);
	for (int i = 0; i < DIVISOR_Y; i++){
		this->DrawScaleYDlts(pDC, m_maxY - (i*unitY), rect, GREY);
	}
	this->DrawScaleYDlts(pDC, m_minY, rect, BLACK);
	if (m_maxY > 0 && m_minY < 0){
		this->DrawScaleYDlts(pDC, 0, rect, RED);
	}

	const int DIVISOR_X = 5;
	double rangeX = TEMPERATURE_MAX - TEMPERATURE_MIN ;
	double unitX = rangeX / DIVISOR_X;
	this->DrawScaleXDlts(pDC, TEMPERATURE_MAX, rect, GREY);
	for (int j = 0; j < DIVISOR_X; j++){
		this->DrawScaleXDlts(pDC, TEMPERATURE_MAX - (j*unitX), rect, GREY);
	}
	this->DrawScaleXDlts(pDC, TEMPERATURE_MIN, rect, BLACK);

	if (GetDocument()->m_pSelectedDataArray != NULL){
			this->DrawScaleXDlts(pDC, GetDocument()->m_pSelectedDataArray->GetTemperature() +273, rect, GREEN);
	}


	pDC->SelectObject(old);

	pen.DeleteObject();
	pen.DeleteObject();

}

void CDLTSguiView::DrawScaleYDlts(CDC* pDC, double value, CRect &rect, COLORREF lineColor)
{
	CString strLabel;
	strLabel.Format("%1.3f pF", value);
	CPoint scalePnt = this->ScalePointDlts(TEMPERATURE_MIN, value, rect);

	int textLength = strLabel.GetLength() * 8;
	int textHeight = 12;
	pDC->SetTextColor(BLACK);
	pDC->TextOut(scalePnt.x - textLength, scalePnt.y - (textHeight/2), strLabel);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, lineColor );
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(scalePnt.x, scalePnt.y);
	pDC->LineTo(pointMax.x, scalePnt.y);
		

	pDC->SelectObject(old);
	pen.DeleteObject();
}

void CDLTSguiView::DrawScaleXDlts(CDC *pDC, double value, CRect &rect, COLORREF lineColor)
{
	CString strLabel;
	strLabel.Format("%1.0f K", (value ));
	CPoint scalePnt = this->ScalePointDlts(value, m_minY, rect);

	int textLength = strLabel.GetLength() * 8;
	int textHeight = 12;
	pDC->SetTextColor(BLACK);
	pDC->TextOut(scalePnt.x - (textLength/2), scalePnt.y + textHeight, strLabel);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, lineColor );
	CPen *old = pDC->SelectObject(&pen);

	CPoint pointMax;
	pointMax.x = rect.right;
	pointMax.y = rect.top;

	pDC->MoveTo(scalePnt.x, scalePnt.y);
	pDC->LineTo(scalePnt.x, pointMax.y);
		

	pDC->SelectObject(old);
	pen.DeleteObject();
}


void CDLTSguiView::DrawLegendDlts(CDC *pDC, CRect &rect)
{
	if (GetDocument()->m_pSelectedDataArray != NULL){
		CString strTemp;
		double value = GetDocument()->DoubleBoxCar(GetDocument()->m_pSelectedDataArray);
		strTemp.Format("dC(t1-t2): %3.3fpF", value);
		pDC->TextOut(rect.left, rect.top - 20, strTemp);
		UpdateData(FALSE);
	}

}


void CDLTSguiView::DrawGraphDlts(CDC* pDC, CRect &rect)
{

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, BLUE);
	CPen *old = pDC->SelectObject(&pen);

	if (GetDocument()->m_pSelectedDataArray == NULL){
		return;
	}
	GetDocument()->m_pSelectedDataArray->SetFirstPosition();
	if (!GetDocument()->m_pSelectedDataArray->HasNext()){
		return;
	}
	
	bool bFirst = true;
	
	CRgn rgn;
	CPoint topLeft = rect.TopLeft();
	CPoint bottomRight = rect.BottomRight();
	rgn.CreateRectRgn(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	pDC->SelectClipRgn( & rgn);
	GetDocument()->GetDataArrayList()->SetFirstPosition();
	while (GetDocument()->GetDataArrayList()->HasNext()){
		CDataArray *dataArray = GetDocument()->GetDataArrayList()->GetNext();
		double value = 0;
		if (m_bDoubleBoxCar){
			value = GetDocument()->DoubleBoxCar(dataArray);
		} else {
			value = GetDocument()->Lokin(dataArray);
		}
		CPoint drawPoint = ScalePointDlts(dataArray->GetTemperature() + 273, value, rect);

		int x1 = drawPoint.x - 2;
		int x2 = drawPoint.x + 2;
		int y1 = drawPoint.y - 2;
		int y2 = drawPoint.y + 2;

		pDC->Ellipse(  x1,  y1,  x2,  y2 );
		pDC->FloodFill( drawPoint.x, drawPoint.y, BLUE );

	}
	pDC->SelectObject(old);
	pen.DeleteObject();

	CRect clientRect;
	GetClientRect(&clientRect);
	CRgn clientRgn;
	clientRgn.CreateRectRgn(clientRect.TopLeft().x, clientRect.TopLeft().y, clientRect.BottomRight().x, clientRect.BottomRight().y);
	pDC->SelectClipRgn( & clientRgn);

}


CPoint CDLTSguiView::ScalePointDlts(double x, double y, CRect drawRect)
{

	double rangeX = TEMPERATURE_MAX - TEMPERATURE_MIN;
	double rangeY = m_maxY - m_minY;

	double unitX = (drawRect.right - drawRect.left) / rangeX;
	double unitY = (drawRect.bottom - drawRect.top) / rangeY;

	CPoint drawPoint;
	drawPoint.x = (long) ceil(x * unitX) - (long) ceil(TEMPERATURE_MIN * unitX) + drawRect.left;
	// convert rect 'normal' ko orientation.
	drawPoint.y = drawRect.bottom - ((long) ceil(y * unitY) - (long) ceil(m_minY * unitY));
	return drawPoint;
}



void CDLTSguiView::CalculateDiagramRange(CDataArray *dataArray)
{
	if (GetDocument()->m_pSelectedDataArray == NULL){
		return;
	}


	if ( !bValidRange && (GetDocument()->m_ctMaxX - GetDocument()->m_ctMinX == 0)){
		bValidRange = true;
		m_maxX = 0;
		m_minX = 0;
		m_maxY = 0;
		m_minY = 0;
		dataArray->SetFirstPosition();
		while (dataArray->HasNext())
		{
			CDataElement *element = dataArray->GetNext();
			if (element->getValue() > m_maxY){
				m_maxY = element->getValue();
			} else if (element->getValue() < m_minY){
				m_minY = element->getValue();
			}

			if (element->getTime() > m_maxX){
				m_maxX = element->getTime();
			} else if (element->getTime() < m_minX){
				m_minX = element->getTime();
			}
		}

	}
}


/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView printing

BOOL CDLTSguiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDLTSguiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDLTSguiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView diagnostics

#ifdef _DEBUG
void CDLTSguiView::AssertValid() const
{
	CView::AssertValid();
}

CDLTSguiDoc* CDLTSguiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDLTSguiDoc)));
	return (CDLTSguiDoc*)m_pDocument;
}
void CDLTSguiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG

void CDLTSguiView::OnFileImport() 
{
	CString filter = "Data files (*.dat) | *.dat|";
	CString defName = "*.dat";
	CFileDialog fileDialog(TRUE, NULL, defName, OFN_HIDEREADONLY, filter);
	fileDialog.m_ofn.lpstrTitle = "Import *.dat file";
	if (fileDialog.DoModal() == IDOK){
		CString fileName = fileDialog.GetPathName();
		CStdioFile file;
		if (!file.Open(fileName, CFile::modeRead)){
			AfxMessageBox("Error while open file!", MB_OK | MB_ICONSTOP);
		} else {
			CFileStatus status;
			if (!file.GetStatus(status)){
				AfxMessageBox("Error while reading file!", MB_OK | MB_ICONSTOP);
			}
			CWaitCursor waitCursor;
			GetDocument()->ImportFile(file);
		}
		
	}
	
}



UINT StartMeasurement2( LPVOID pParam ){
	CDLTSguiDoc * pDoc= (CDLTSguiDoc*)pParam;

	try { GetDltsDevice()->start(pDoc); } catch( ... ) {
		console.writeln("error while starting c/t");
		GetDltsDevice()->m_pThread = NULL;
		return 1;
	}
	return 0;
}


void CDLTSguiView::OnFileStartCt() 
{
	if (GetDltsDevice()->isRunning()){
		AfxMessageBox("Measurement is in progress", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (ShowProperties() == IDOK){
		GetDltsDevice()->m_pThread = AfxBeginThread(StartMeasurement2, GetDocument());
		DWORD error = GetLastError();
	}	
}




void CDLTSguiView::OnFileStartCu() 
{
	if (GetDltsDevice()->isRunning()){
		AfxMessageBox( "Measurement is in progress", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

}

void CDLTSguiView::OnUpdateMenuFile(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetDltsDevice()->isRunning());
}



void CDLTSguiView::OnFileStopMeasurement() 
{
	GetDltsDevice()->setAbortFlag();
}

void CDLTSguiView::OnUpdateFileStopMeasurement(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDltsDevice()->isRunning());
}

void CDLTSguiView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CFrameWnd *pFrame = GetParentFrame();
	if (pFrame->IsKindOf(RUNTIME_CLASS(CChildFrame))){
		CChildFrame *pChild = (CChildFrame*) pFrame;
		pChild->m_pWorkspaceWnd->UpdateCurrentView();
	}
	Invalidate(TRUE);
}




/////////////////////////////////////////////////////////////////////////////
// CDLTSguiView message handlers



void CDLTSguiView::OnGraphProperties() 
{

	CGraphProperties properties;
	properties.m_maxX = m_maxX / 100.0;
	properties.m_maxY = m_maxY;
	properties.m_minX = m_minX;
	properties.m_minY = m_minY; 

	if (properties.DoModal() == IDOK){
		m_maxX = properties.m_maxX * 100.0;
		m_maxY = properties.m_maxY;
		m_minX = properties.m_minX;
		m_minY = properties.m_minY;
	}
	Invalidate();
}

void CDLTSguiView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	CRect rect;
	GetWindowRect(rect);
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_VISIBLE_AREA, "Range");
	menu.AppendMenu(MF_STRING, ID_EDIT_PROPERTIES, "Properties");
	menu.AppendMenu(MF_STRING | MF_SEPARATOR , 0, "Graph");

//	menu.AppendMenu(MF_STRING, ID_VISIBLE_AREA_ALL, "range (all views)");
//	menu.AppendMenu(MF_STRING, ID_VISIBLE_AREA_RESET, "reset range (current view)");
//	menu.AppendMenu(MF_STRING, ID_VISIBLE_AREA_RESET_ALL, "reset range (all views)");
	if (m_bShowTransient){
		menu.AppendMenu(MF_STRING | MF_CHECKED, ID_GRAPH_CT, "C/t graph");
	} else {
		menu.AppendMenu(MF_STRING, ID_GRAPH_CT, "C/t graph");
	}
	if (m_bShowDltsDiagram){
		menu.AppendMenu(MF_STRING | MF_CHECKED, ID_GRAPH_DLTS, "DLTS graph");
	} else {
		menu.AppendMenu(MF_STRING, ID_GRAPH_DLTS, "DLTS graph");
	}
	

	menu.AppendMenu(MF_STRING | MF_SEPARATOR , 0, "Algorithm");
	if (!m_bShowDltsDiagram){
		menu.AppendMenu(MF_STRING | MF_GRAYED, ID_GRAPH_DOUBLE_BC, "Double Boxcar");
		menu.AppendMenu(MF_STRING | MF_GRAYED, ID_GRAPH_LOKIN, "Lock-In");
	} else {
		if (m_bDoubleBoxCar){
			menu.AppendMenu(MF_STRING | MF_CHECKED, ID_GRAPH_DOUBLE_BC, "Double Boxcar");
			menu.AppendMenu(MF_STRING, ID_GRAPH_LOKIN, "Lock-In");
		} else {
			menu.AppendMenu(MF_STRING, ID_GRAPH_DOUBLE_BC, "Double Boxcar");
			menu.AppendMenu(MF_STRING | MF_CHECKED, ID_GRAPH_LOKIN, "Lock-in");
		}
	}


	menu.TrackPopupMenu(TPM_LEFTBUTTON | TPM_CENTERALIGN, point.x + rect.left, point.y + rect.top, this, NULL);
	
	CView::OnRButtonDown(nFlags, point);
}


void CDLTSguiView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	if ( (GetDocument()->m_ctMaxX - GetDocument()->m_ctMinX != 0) &&
		(GetDocument()->m_ctMaxY - GetDocument()->m_ctMinY != 0)){
		m_maxX = GetDocument()->m_ctMaxX;
		m_minX = GetDocument()->m_ctMinX;
		m_maxY = GetDocument()->m_ctMaxY;
		m_minY = GetDocument()->m_ctMinY;
	}

	CFrameWnd *pFrame = GetParentFrame();
	if (pFrame->IsKindOf(RUNTIME_CLASS(CChildFrame))){
		CChildFrame *pChild = (CChildFrame*) pFrame;
		pChild->m_pWorkspaceWnd->SetDocument(GetDocument());
		pChild->m_pWorkspaceWnd->UpdateListContent();
	}
}

void CDLTSguiView::OnVisibleAreaReset() 
{
	m_maxX = 0;
	m_minX = 0;
	m_maxY = 0;
	m_minY = 0;
	Invalidate();
}


void CDLTSguiView::OnWriteVoltage() 
{
	if (GetDltsDevice()->isRunning()){
		AfxMessageBox( "Measurement is in progress", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CVoltageOutDialog dialog;
	dialog.m_voltageOut = GetDocument()->getReverseVoltage();
	if (dialog.DoModal() == IDOK) {
		dialog.m_voltageOut;
		GetDltsDevice()->writeVoltage(dialog.m_voltageOut);
	}
}


void CDLTSguiView::OnEditProperties() 
{
	ShowProperties();
}

BOOL CDLTSguiView::ShowProperties()
{
	float Tcurrent = GetDltsDevice()->getCurrentTemp();

	CPropertyDlg parameters;
	parameters.m_tempStart = Tcurrent;
	parameters.m_pulseWidth = GetDocument()->getPulseWidth();
	parameters.m_delay = GetDocument()->getDelay();
	parameters.m_numAveraging = GetDocument()->getNumberOfAveragings();
	parameters.m_gain = GetDocument()->getGain();
	parameters.m_reverseVoltage = GetDocument()->getReverseVoltage();
	parameters.m_pulseVoltage = GetDocument()->getPulseVoltage();
	parameters.m_tempEnd = GetDocument()->getEndTemp();
	parameters.m_tempStep = GetDocument()->getTempStep();
	parameters.m_singleTemperature = GetDocument()->getSingleTemperature();
	parameters.m_t1 = GetDocument()->m_t1 / 100.0;
	parameters.m_t2 = GetDocument()->m_t2 / 100.0;
	parameters.m_tempDeviance = GetDocument()->getTempDeviance();
	parameters.m_bEnable = !GetDltsDevice()->isRunning();

	parameters.m_rangeMultiplier = GetDltsDevice()->getBoonton()->getRangeMultiplier();
	if (parameters.DoModal() == IDOK){
		int numAveraging = parameters.m_numAveraging;
		float pulseVoltage = parameters.m_pulseVoltage;
		int pulseWidth = parameters.m_pulseWidth;
		float reverseVoltage = parameters.m_reverseVoltage;
		int t1 = parameters.m_t1;
		int t2 = parameters.m_t2;
		
		float tempEnd = parameters.m_tempEnd;
		float tempBegin = parameters.m_tempStart;
		float tempStart = parameters.m_tempStart;
		float tempStep = parameters.m_tempStep;
		int delay = parameters.m_delay;
		int gain = parameters.m_gain;
		bool singleTemp = (parameters.m_singleTemperature != 0);
		int rangeMultiplier = parameters.m_rangeMultiplier;
		GetDocument()->setPulseWidth(pulseWidth);
		GetDocument()->setDelay(delay);
		GetDocument()->setNumberOfAveragings(numAveraging);
		GetDocument()->setGain(gain);
		GetDocument()->setReverseVoltage(reverseVoltage);
		GetDocument()->setPulseVoltage(pulseVoltage);
		GetDocument()->setStartTemp(tempStart);
		GetDocument()->setEndTemp(tempEnd);
		GetDocument()->setTempStep(tempStep);
		GetDocument()->setSingleTemperature(singleTemp);
		GetDltsDevice()->getBoonton()->setRangeMultiplier(rangeMultiplier);
		GetDocument()->m_t1 = parameters.m_t1 * 100.0; 
		GetDocument()->m_t2 = parameters.m_t2 * 100.0;
		GetDocument()->setTempDeviance(parameters.m_tempDeviance);


		CWinApp * pApp = AfxGetApp();

		pApp->WriteProfileInt("DLTS Settings","delay", delay);
		pApp->WriteProfileInt("DLTS Settings","gain", gain);
		pApp->WriteProfileInt("DLTS Settings","numberOfAveraging", numAveraging);
		pApp->WriteProfileInt("DLTS Settings","pulseWidth", pulseWidth);
		double value = pulseVoltage * 10.0;
		pApp->WriteProfileInt("DLTS Settings","pulseVoltage", (int) floor(value));

		value = reverseVoltage * 10.0;
		pApp->WriteProfileInt("DLTS Settings","reverseVoltage", (int) floor(value));
		value = tempEnd * 10.0;
		pApp->WriteProfileInt("DLTS Settings","tempEnd", (int) floor(value));
		value = tempStep * 10.0;
		pApp->WriteProfileInt("DLTS Settings","tempStep", (int) floor(value));
		pApp->WriteProfileInt("DLTS Settings","singleTemp", singleTemp);

		pApp->WriteProfileInt("DLTS Settings","t1", GetDocument()->m_t1);
		pApp->WriteProfileInt("DLTS Settings","t2", GetDocument()->m_t2);

		GetDocument()->UpdateAllViews();
		return IDOK;
	}	
	return IDCANCEL;

}



void CDLTSguiView::OnEditBoontonZero() 
{
	GetDltsDevice()->getBoonton()->SetZero();
}





void CDLTSguiView::OnGraphCt() 
{
	if (m_bShowTransient){
		m_bShowTransient = false;
		if (!m_bShowDltsDiagram){
			m_bShowDltsDiagram = true;
		}
	} else {
		m_bShowTransient = true;
	}
	Invalidate(TRUE);
}

void CDLTSguiView::OnUpdateGraphCt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowTransient);	
}

void CDLTSguiView::OnGraphDlts() 
{
	if (m_bShowDltsDiagram){
		m_bShowDltsDiagram = false;
		if (!m_bShowTransient){
			m_bShowTransient = true;
		}
	} else {
		m_bShowDltsDiagram = true;
	}

	Invalidate(TRUE);
}

void CDLTSguiView::OnUpdateGraphDlts(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowDltsDiagram);
	
}



void CDLTSguiView::OnGraphDoubleBc() 
{
	if (m_bDoubleBoxCar){
		m_bDoubleBoxCar = false;
	} else {
		m_bDoubleBoxCar = true;
	}
	Invalidate(TRUE);

}

void CDLTSguiView::OnUpdateGraphDoubleBc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bShowDltsDiagram);
	pCmdUI->SetCheck(m_bDoubleBoxCar);
	
}

void CDLTSguiView::OnGraphLokin() 
{
	if (m_bDoubleBoxCar){
		m_bDoubleBoxCar = false;
	} else {
		m_bDoubleBoxCar = true;
	}
	Invalidate(TRUE);
}

void CDLTSguiView::OnUpdateGraphLokin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bShowDltsDiagram);
	pCmdUI->SetCheck(!m_bDoubleBoxCar);
	
}
