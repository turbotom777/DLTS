// ListFrame.cpp : implementation file
//

#include "stdafx.h"
#include "dltsgui.h"
#include "ListFrame.h"
#include "DataArray.h"
#include "DataArrayList.h"
#include "DLTSguiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListFrame

CListFrame::CListFrame()
{
	m_ListCtrlCt = new CListCtrl();
	m_pImageList = new CImageList();
	m_activeDocument = NULL;
	m_sortDirection = 1;
}

CListFrame::~CListFrame()
{
    if (m_ListCtrlCt != NULL) {
        delete m_ListCtrlCt;
    }
	if (m_pImageList != NULL){
		delete m_pImageList;
	}

}


BEGIN_MESSAGE_MAP(CListFrame, CWnd)
	//{{AFX_MSG_MAP(CListFrame)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTR_CT, OnKeydown)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTR_CT, OnDoubleClick )
	ON_NOTIFY(NM_CLICK, IDC_LIST_CTR_CT, OnClick )
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CTR_CT, OnColumnClick)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListFrame message handlers
void CListFrame::OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult){
	int i = 0;
}

void CListFrame::OnClick(NMHDR* pNMHDR, LRESULT* pResult){
	if (m_activeDocument != NULL && m_ListCtrlCt->GetItemCount() > 0){
		int pos = m_ListCtrlCt->GetSelectionMark( );
		CDataArray* dataArray = (CDataArray*) m_ListCtrlCt->GetItemData(pos);
		m_activeDocument->m_pSelectedDataArray = dataArray;
		m_activeDocument->UpdateAllViews();
	}
	
}

void CListFrame::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult){
	if (m_activeDocument != NULL && m_ListCtrlCt->GetItemCount() > 0){
		int pos = m_ListCtrlCt->GetSelectionMark( );
		CDataArray* dataArray = (CDataArray*) m_ListCtrlCt->GetItemData(pos);
		m_activeDocument->m_pSelectedDataArray = dataArray;
		m_activeDocument->UpdateAllViews();
	}
}

int CListFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	m_ListCtrlCt->Create(
		LVS_ALIGNLEFT | LVS_REPORT  | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_SORTASCENDING |
		WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, this, IDC_LIST_CTR_CT);

	m_ListCtrlCt->SetExtendedStyle( m_ListCtrlCt->GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_ListCtrlCt->InsertColumn(0, "Temp[°C]", LVCFMT_LEFT, 70);
	m_ListCtrlCt->InsertColumn(1, "[K]", LVCFMT_LEFT, 50);
	m_ListCtrlCt->InsertColumn(2, "Averaging", LVCFMT_LEFT, 100);
	//m_ListCtrlCt->InsertColumn(1, "Date", LVCFMT_LEFT, 60);

	m_pImageList->Create(IDB_TEMPERATUR, 16, 1, RGB(255,255,255));
	m_pImageList->SetOverlayImage( 9,		1);
	m_ListCtrlCt->SetImageList(m_pImageList, LVSIL_SMALL);
	return 0;
}

void CListFrame::OnDestroy() 
{
	CWnd::OnDestroy();
	m_ListCtrlCt->DestroyWindow();   
}
	
void CListFrame::UpdateCurrentView()
{
    CRect rc;
    GetClientRect(rc);

	GetClientRect(rc);
	m_ListCtrlCt->MoveWindow(rc);
}


void CListFrame::AddProjectItem(CDataArray *dataArray)
{
	double temperature = dataArray->GetTemperature();
	int averaging = dataArray->GetNumberOfAveraging();
	CString strTemp;
	strTemp.Format("%3.1f", temperature);
	int newItem = m_ListCtrlCt->GetItemCount();
	int pos = m_ListCtrlCt->InsertItem( newItem, strTemp, GetIcon(temperature));
	m_ListCtrlCt->SetItemData( pos, (LPARAM) dataArray );
	
	strTemp.Format("%3.1f", (273 + temperature));
	m_ListCtrlCt->SetItemText( pos, 1, strTemp );
	CString strAveraging;
	strAveraging.Format("%d", averaging);
	m_ListCtrlCt->SetItemText( pos, 2, strAveraging );
	m_ListCtrlCt->SetSelectionMark(pos);
}




void CListFrame::UpdateListContent()
{
	if (m_activeDocument == NULL){
		m_ListCtrlCt->DeleteAllItems();
		return;
	}

	if (m_ListCtrlCt->GetItemCount() != m_activeDocument->GetDataArrayList()->GetItemCount()){
		m_ListCtrlCt->DeleteAllItems();
		CDataArrayList *dataArrayList = m_activeDocument->GetDataArrayList();
		if (dataArrayList != NULL){
			dataArrayList->SetFirstPosition();
			while (dataArrayList->HasNext()){
				CDataArray *dataArray = dataArrayList->GetNext();
				AddProjectItem(dataArray);
			}
		} 
	}
}

int CListFrame::GetIcon(double temperature)
{
	if (temperature > 0){
		return 0;
	} else 	if (temperature < 0 && temperature >= -70){
		return 1;
	} else 	if (temperature < -70 && temperature >= -140){
		return 2;
	} else {
		return 3;
	}  
}


int CALLBACK SortTemperature(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CDataArray *a1 = (CDataArray*)lParam1;
	CDataArray *a2 = (CDataArray*)lParam2;
	int * sortDirection = (int*) lParamSort;

	int value =  (a1->GetTemperature() > a2->GetTemperature()?1:-1);
	return *sortDirection * value;
}

int CALLBACK SortAverage(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CDataArray *a1 = (CDataArray*)lParam1;
	CDataArray *a2 = (CDataArray*)lParam2;
	int * sortDirection = (int*) lParamSort;

	int value =  (a1->GetNumberOfAveraging() > a2->GetNumberOfAveraging()?1:-1);
	return *sortDirection * value;
}



void CListFrame::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;


	int sortedColumn = pNMListView->iSubItem;
	if (m_sortDirection > 0){
		m_sortDirection = -1;
	} else {
		m_sortDirection = 1;
	}
	if (sortedColumn == 0 || sortedColumn == 1){
		m_ListCtrlCt->SortItems(SortTemperature, (DWORD)&m_sortDirection);
	} else if (sortedColumn == 2){
		m_ListCtrlCt->SortItems(SortAverage, (DWORD)&m_sortDirection);
	}
	
	UpdateWindow();

	*pResult = 0;

}


