// DLTSguiDoc.cpp : implementation of the CDLTSguiDoc class
//

#include "stdafx.h"
#include "DLTSgui.h"

#include "DLTSguiDoc.h"
#include "StringTokenizer.h"
#include "math.h"
#include "DataArrayList.h"
#include "DataElement.h"
#include "MainFrm.h"
#include "WorkspaceWnd.h"
#include "graphProperties.h"
#include "DLTSguiView.h"
#include "DLTSdevice.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiDoc

IMPLEMENT_DYNCREATE(CDLTSguiDoc, CDocument)

BEGIN_MESSAGE_MAP(CDLTSguiDoc, CDocument)
	//{{AFX_MSG_MAP(CDLTSguiDoc)
	ON_COMMAND(ID_VISIBLE_AREA_RESET_ALL, OnVisibleAreaResetAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORT, OnUpdateFileImport)
	ON_COMMAND(ID_VISIBLE_AREA_ALL, OnGraphProperties)
	ON_COMMAND(ID_FILE_EXPORTSTATISTIC, OnFileExportStatistic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiDoc construction/destruction

CDLTSguiDoc::CDLTSguiDoc()
{
	
	m_ctMaxX = 0; 
	m_ctMaxY = 0;
	m_ctMinX = 0;
	m_ctMinY = 0;

	m_pulseWidth = 200;
	m_delay = 10;
	m_numberOfAveraging = 1;
	m_gain = 10;
	m_reverseVoltage = -5.0f;
	m_pulseVoltage = 0.3f;

	m_tempStart = 25;
	m_tempEnd = -200.0f;
	m_tempStep = 1.0f;
	m_bSingleTemp = false;
	m_pSelectedDataArray = NULL;
	m_tempDeviance = TEMPERATURE_DEVIANCE_MAX;

	m_t1 = 0;
	m_t2 = 0;
}

CDLTSguiDoc::~CDLTSguiDoc()
{
	if (m_dataArrayList != NULL){
		delete m_dataArrayList;
	}
}




void CDLTSguiDoc::setPulseWidth(int pulseWidth){
	m_pulseWidth = pulseWidth;
}

void CDLTSguiDoc::setDelay(int delay){
	m_delay = delay;
}

void CDLTSguiDoc::setNumberOfAveragings(int numberOfAveraging){
	m_numberOfAveraging = numberOfAveraging;
}

void CDLTSguiDoc::setGain(int gain){
	m_gain = gain;
}

void CDLTSguiDoc::setReverseVoltage(float reverseVoltage){
	m_reverseVoltage = reverseVoltage;
}

void CDLTSguiDoc::setPulseVoltage(float pulseVoltage){
	m_pulseVoltage = pulseVoltage;
}

void CDLTSguiDoc::setStartTemp(float tempStart){
	m_tempStart = tempStart;
}

void CDLTSguiDoc::setEndTemp(float tempEnd){
	m_tempEnd = tempEnd;
}

void CDLTSguiDoc::setTempStep(float tempStep){
	m_tempStep = tempStep;
}

void CDLTSguiDoc::setSingleTemperature(bool bSingleTemp){
	m_bSingleTemp = bSingleTemp;
}

bool CDLTSguiDoc::getSingleTemperature(){
	return m_bSingleTemp;
}

int CDLTSguiDoc::getPulseWidth(){
	return m_pulseWidth;
}
int CDLTSguiDoc::getDelay(){
	return m_delay;
}
int CDLTSguiDoc::getNumberOfAveragings(){
	return m_numberOfAveraging;
}
int CDLTSguiDoc::getGain(){
	return m_gain;
}
float CDLTSguiDoc::getReverseVoltage(){
	return m_reverseVoltage;
}
float CDLTSguiDoc::getPulseVoltage(){
	return m_pulseVoltage;
}
float CDLTSguiDoc::getStartTemp(){
	return m_tempStart;
}
float CDLTSguiDoc::getEndTemp(){
	return m_tempEnd;
}
float CDLTSguiDoc::getTempStep(){
	return m_tempStep;
}
bool CDLTSguiDoc::isSingleTemperature(){
	return m_bSingleTemp;
}


float CDLTSguiDoc::getNextTemperature(float Tsetpoint){
	if (m_bSingleTemp){
		return m_tempStart;
	}

	if (m_tempStart > m_tempEnd){
		Tsetpoint -= m_tempStep;
	} else {
		Tsetpoint += m_tempStep;
	}
	return Tsetpoint;
}


bool CDLTSguiDoc::reachedEndTemperature(float TcurSetpoint){
	if (m_bSingleTemp){
		return false;
	}

	if (m_tempStart >= m_tempEnd){
		if (TcurSetpoint <= m_tempEnd){
			return true;
		} 
	} else {
		if (TcurSetpoint >= m_tempEnd){
			return true;
		}
	}
	return false;
}




/////////////////////////////////////////////////////////////////////////////
// CDLTSguiDoc serialization

void CDLTSguiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		float fileVersion = FILE_VERSION;
		ar << fileVersion;
		// version 1.1
		ar << m_t1;
		ar << m_t2;
		// version 1.2
		ar << m_ctMaxX;
		ar << m_ctMaxY;
		ar << m_ctMinX;
		ar << m_ctMinY;

		ar << m_pulseWidth;
		ar << m_delay;
		ar << m_numberOfAveraging;
		ar << m_gain;
		ar << m_reverseVoltage;
		ar << m_pulseVoltage;
		ar << m_dataArrayList;
	}
	else
	{
		float fileVersion;
		ar >> fileVersion;
		if (fileVersion >= 1.1){
			ar >> m_t1;
			ar >> m_t2;
		}
		if (fileVersion >= 1.2){
			ar >> m_ctMaxX;
			ar >> m_ctMaxY;
			ar >> m_ctMinX;
			ar >> m_ctMinY;
		}
		ar >> m_pulseWidth;
		ar >> m_delay;
		ar >> m_numberOfAveraging;
		ar >> m_gain;
		ar >> m_reverseVoltage;
		ar >> m_pulseVoltage;
		ar >> m_dataArrayList;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiDoc diagnostics

#ifdef _DEBUG
void CDLTSguiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDLTSguiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiDoc commands



BOOL CDLTSguiDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

void CDLTSguiDoc::ImportFile(CStdioFile & file) 
{
	if (m_dataArrayList != NULL){
		delete m_dataArrayList;
		//GetWorkspaceWnd()->UpdateListContent(NULL);
		m_dataArrayList = new CDataArrayList();	
		m_pSelectedDataArray = NULL;
	}

	CString content;
	DWORD length = file.GetLength(); 
	int size = file.Read(content.GetBuffer(length), length);
	content.ReleaseBuffer(size);
	StringTokenizer lineToken(content, '\n');
	if (lineToken.hasMoreTokens()){
		CString firstLine = lineToken.nextToken();
		StringTokenizer csvToken(firstLine, ',');
		while (csvToken.hasMoreTokens()) {
			double temperature = parseNumber(csvToken.nextToken());
			CDataArray *dataArray = new CDataArray();
			dataArray->SetTemperature(temperature);
			m_dataArrayList->AddElement(dataArray);
		}
	}
	int time = 0;
	while (lineToken.hasMoreTokens()){
		CString line = lineToken.nextToken();
		StringTokenizer csvToken(line, ',');
		m_dataArrayList->SetFirstPosition();
		while (csvToken.hasMoreTokens() && m_dataArrayList->HasNext()) {
			CDataArray *dataArray = m_dataArrayList->GetNext();
			CString next = csvToken.nextToken();
			double value = parseNumber(next);
			CDataElement *element = new CDataElement(value, time);
			dataArray->AddElement(element);
		}
		time++;
	}
	SetModifiedFlag(TRUE);
	UpdateAllViews();	
}
double CDLTSguiDoc::parseNumber(CString strNumber){
	double number = 0.0;
	strNumber.TrimLeft();
	strNumber.TrimRight();
	bool negativ = false;
	if (strNumber.GetAt(0) == '-'){
		negativ = true;
		strNumber.Delete(0);
	}
	bool bDot = false;

	int expo = 1;
	for (int j = 0; j < strNumber.GetLength(); j++){
		if (strNumber.GetAt(j) == '.'){
			bDot = true;
			continue;
		} else if (strNumber.GetAt(j) < 48 || strNumber.GetAt(j) > 57){
			number = 0;
			break;
		}
		if (bDot){
			double divisor =  pow(10.0, expo);
			double floatPart = (strNumber.GetAt(j) - 48)/ divisor;
			number += floatPart;
			expo++;
		} else {
			number *= 10;
			number += (strNumber.GetAt(j) - 48) ; 
		}
	}

	if (negativ){
		number = number * -1;
	}
	return number;
}


void CDLTSguiDoc::UpdateAllViews()
{
	CDocument::UpdateAllViews(NULL);
	//GetWorkspaceWnd()->UpdateListContent(this);
}

void CDLTSguiDoc::OnCloseDocument() 
{
//	GetWorkspaceWnd()->UpdateListContent(NULL);
	CDocument::OnCloseDocument();
}
CDataArrayList* CDLTSguiDoc::GetDataArrayList(){
	return m_dataArrayList;
}


/*
CWorkspaceWnd * CDLTSguiDoc::GetWorkspaceWnd()
{	
	CWnd *mainWnd = AfxGetMainWnd();
	if (mainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame))){
		CMainFrame *mainFrame = (CMainFrame*) mainWnd;
		return mainFrame->GetWorkspaceWnd();
	}
	return NULL;
}
*/

void CDLTSguiDoc::OnGraphProperties() 
{
	CDLTSguiView *dltsView = GetCurrentView();
	if (dltsView != NULL){
		m_ctMaxX = dltsView->m_maxX;
		m_ctMaxY = dltsView->m_maxY;
		m_ctMinX = dltsView->m_minX;
		m_ctMinY = dltsView->m_minY;
	}

	CGraphProperties properties;
	properties.m_maxX = m_ctMaxX;
	properties.m_maxY = m_ctMaxY;
	properties.m_minX = m_ctMinX;
	properties.m_minY = m_ctMinY; 

	if (properties.DoModal() == IDOK){
		m_ctMaxX = properties.m_maxX;
		m_ctMaxY = properties.m_maxY;
		m_ctMinX = properties.m_minX;
		m_ctMinY = properties.m_minY;

		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			if (pView->IsKindOf(RUNTIME_CLASS(CDLTSguiView))){
				CDLTSguiView *dltsView = (CDLTSguiView*) pView;
				dltsView->m_maxX = m_ctMaxX;
				dltsView->m_maxY = m_ctMaxY;
				dltsView->m_minX = m_ctMinX;
				dltsView->m_minY = m_ctMinY;
			}
		}
		CDocument::UpdateAllViews(NULL);
	}

}

void CDLTSguiDoc::OnVisibleAreaResetAll() 
{
	m_ctMaxX = 0;
	m_ctMaxY = 0;
	m_ctMinX = 0;
	m_ctMinY = 0;

	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CDLTSguiView))){
			CDLTSguiView *dltsView = (CDLTSguiView*) pView;
			dltsView->m_maxX = m_ctMaxX;
			dltsView->m_maxY = m_ctMaxY;
			dltsView->m_minX = m_ctMinX;
			dltsView->m_minY = m_ctMinY;
		}
	}
	CDocument::UpdateAllViews(NULL);
}

CDLTSguiView* CDLTSguiDoc::GetCurrentView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView == CWnd::GetFocus()){
			if (pView->IsKindOf(RUNTIME_CLASS(CDLTSguiView))){
				return (CDLTSguiView*) pView;
			}
		}
	}
	return NULL;
}

void CDLTSguiDoc::OnUpdateFileImport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsModified());
}

BOOL CDLTSguiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_dataArrayList = new CDataArrayList();

	CWinApp * pApp = AfxGetApp();
	m_delay = pApp->GetProfileInt("DLTS Settings","delay", m_delay);
	m_gain = pApp->GetProfileInt("DLTS Settings","gain", m_gain);
	m_numberOfAveraging = pApp->GetProfileInt("DLTS Settings","numberOfAveraging", m_numberOfAveraging);
	m_pulseWidth = pApp->GetProfileInt("DLTS Settings","pulseWidth", m_pulseWidth);

	int regValue = pApp->GetProfileInt("DLTS Settings","pulseVoltage", -10 );
	m_pulseVoltage =  regValue / 10.0f;
	
	regValue = pApp->GetProfileInt("DLTS Settings","reverseVoltage", -60 );
	m_reverseVoltage = regValue / 10.0f;

	regValue = pApp->GetProfileInt("DLTS Settings","tempEnd", -1900);
	m_tempEnd = regValue / 10.0f;

	regValue = pApp->GetProfileInt("DLTS Settings","tempStep", 10);
	m_tempStep = regValue / 10.0f;

	regValue = pApp->GetProfileInt("DLTS Settings","singleTemp", 0);
	if (regValue != 0){
		m_bSingleTemp = true;
	}  else {
		m_bSingleTemp = false;
	}

	m_t1 = pApp->GetProfileInt("DLTS Settings","t1", 100);
	m_t2 = pApp->GetProfileInt("DLTS Settings","t2", 1000);


	return TRUE;
}

BOOL CDLTSguiDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CWinApp * pApp = AfxGetApp();

	pApp->WriteProfileInt("DLTS Settings","delay", m_delay);
	pApp->WriteProfileInt("DLTS Settings","gain", m_gain);
	pApp->WriteProfileInt("DLTS Settings","numberOfAveraging", m_numberOfAveraging);
	pApp->WriteProfileInt("DLTS Settings","pulseWidth", m_pulseWidth);
	pApp->WriteProfileInt("DLTS Settings","pulseVoltage", (int) ceil(m_pulseVoltage * 10));

	pApp->WriteProfileInt("DLTS Settings","reverseVoltage", (int) ceil(m_reverseVoltage * 10));
	pApp->WriteProfileInt("DLTS Settings","tempEnd", (int) ceil(m_tempEnd * 10));
	pApp->WriteProfileInt("DLTS Settings","tempStep", (int) ceil(m_tempStep * 10));
	pApp->WriteProfileInt("DLTS Settings","singleTemp", m_bSingleTemp);


	return CDocument::OnSaveDocument(lpszPathName);
}

double CDLTSguiDoc::DoubleBoxCar(CDataArray *dataArray)
{
	double valueT1 = 0;
	double valueT2 = 0;
	int count = 0;
	dataArray->SetFirstPosition();
	while (dataArray->HasNext()){
		CDataElement *element = dataArray->GetNext();
		if (element->getTime() >= m_t1 && element->getTime() < (m_t1 + 10)){
			valueT1 += element->getValue();
			count++;
		}
	}
	valueT1 = valueT1/count;

	count = 0;
	dataArray->SetFirstPosition();
	while (dataArray->HasNext()){
		CDataElement *element = dataArray->GetNext();
		if (element->getTime() >= m_t2 && element->getTime() < (m_t2 + 10) ){
			valueT2 += element->getValue();
			count++;
		}
	}

	valueT2 = valueT2/count;
	return valueT1 - valueT2;

}

float CDLTSguiDoc::getTempDeviance()
{
	return m_tempDeviance;
}

void CDLTSguiDoc::setTempDeviance(float deviance)
{
	m_tempDeviance = deviance;
}

double CDLTSguiDoc::Lokin(CDataArray *dataArray)
{
	double valueT1 = 0;
	double valueT2 = 0;
	int count = 0;

	int middle = (m_t2 - m_t1) /2;
	dataArray->SetFirstPosition();
	while (dataArray->HasNext()){
		CDataElement *element = dataArray->GetNext();
		if (element->getTime() >= m_t1 && element->getTime() < middle){
			valueT1 += element->getValue();
			count++;
		}
	}
	valueT1 = valueT1/count;

	count = 0;
	dataArray->SetFirstPosition();
	while (dataArray->HasNext()){
		CDataElement *element = dataArray->GetNext();
		if (element->getTime() >= middle && element->getTime() < m_t2 ){
			valueT2 += element->getValue();
			count++;
		}
	}

	valueT2 = valueT2/count;
	return 2* (valueT1 - valueT2);

}

void CDLTSguiDoc::OnFileExportStatistic() 
{
	CFileDialog *dialog;
	dialog = new CFileDialog(FALSE, NULL, NULL, OFN_HIDEREADONLY, "dat Dateien (*.dat)|*.dat|");
	if (dialog->DoModal() == IDOK){
		CString sFileName;
		CFile file;
		sFileName = dialog->GetPathName();
		int exits = file.Open(sFileName, CFile::modeWrite | CFile::modeCreate);

		CString legend("nb of averages, standard difference [fF]\r\n");
		file.Write(legend.GetBuffer(legend.GetLength()), legend.GetLength());
		m_dataArrayList->SetFirstPosition();
		while (m_dataArrayList->HasNext()){
			CDataArray *dataArray = m_dataArrayList->GetNext();
			int count = 0;
			double value = 0.0;
			dataArray->SetFirstPosition();
			while (dataArray->HasNext()){
				CDataElement *element = dataArray->GetNext();
				if (element->getTime() >= m_t1 && element->getTime() < m_t2){
					value += element->getValue();
					count++;
				}
			}
			double meanValue = value/count;
			count = 0;
			value = 0;
			dataArray->SetFirstPosition();
			while (dataArray->HasNext()){
				CDataElement *element = dataArray->GetNext();
				if (element->getTime() >= m_t1 && element->getTime() < m_t2 ){
					value += pow(meanValue - element->getValue(), 2);
					count++;
				}
			}
			int average = dataArray->GetNumberOfAveraging();
			double diff = sqrt(value/ count) * 1000000;
			CString str;
			str.Format("%d, %3,5\r\n", average, diff);
			file.Write(str.GetBuffer(str.GetLength()), str.GetLength());
		}
	}

}
