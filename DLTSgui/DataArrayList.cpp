// DataArrayList.cpp: implementation of the CDataArrayList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dltsgui.h"
#include "DataArrayList.h"
#include "DataArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDataArrayList, CObject, 1)


CDataArrayList::CDataArrayList()
{
	m_pos = NULL;
}

CDataArrayList::~CDataArrayList()
{
	POSITION pos = m_elementList.GetHeadPosition();
	while (pos != NULL){
		CDataArray* element = (CDataArray*) m_elementList.GetNext(pos);
		delete element;
	}
}

void CDataArrayList::AddElement(CDataArray *element){
	m_elementList.AddTail(element);
}

void CDataArrayList::SetFirstPosition(){
	if (m_elementList.IsEmpty()){
		m_pos = NULL;
	}
	m_pos = m_elementList.GetHeadPosition();
}

CDataArray* CDataArrayList::GetNext(){
	if (m_pos != NULL){
		return (CDataArray*) m_elementList.GetNext(m_pos);
	}
	return NULL;
}

bool CDataArrayList::HasNext(){
	return m_pos != NULL;
}


void CDataArrayList::Serialize(CArchive &ar)
{
	CObject::Serialize( ar ); 
	
	if (ar.IsStoring()){
		float fileVersion = FILE_VERSION;
		ar << fileVersion;
		SetFirstPosition();
		int count = 0;
		SetFirstPosition();
		while (HasNext()){
			GetNext();
			count++;
		}

		ar << count;
		SetFirstPosition();
		while (HasNext()){
			CDataArray* dataArray = GetNext();
			ar << dataArray;
		}
		
	} else {
		float fileVersion;
		ar >> fileVersion;

		int count;
		ar >> count;
		for (int i = 0; i < count; i++){
			CDataArray* dataArray;
			ar >> dataArray;
			this->AddElement(dataArray);
			/*
			if (dataArray->GetTemperature() > -95.0f){
				this->AddElement(dataArray);
			} else {
				delete dataArray;
			}
			*/
			
		}
	}

}



int CDataArrayList::GetItemCount()
{
	int count = 0;
	POSITION pos = m_elementList.GetHeadPosition();
	while (pos != NULL){
		CDataArray* element = (CDataArray*) m_elementList.GetNext(pos);
		count++;
	}
	return count;
}
