// DataArray.cpp: implementation of the CDataArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dltsgui.h"
#include "DataArray.h"
#include "DataElement.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDataArray, CObject, 1)

CDataArray::CDataArray(){
	m_pos = NULL;
	m_time = NULL;
}

CDataArray::~CDataArray(){
	POSITION pos = m_elementList.GetHeadPosition();
	while (pos != NULL){
		CDataElement* element = (CDataElement*) m_elementList.GetNext(pos);
		delete element;
	}
	if (m_time != NULL){
		delete m_time;
	} 
}

void CDataArray::AddElement(CDataElement *element){
	m_elementList.AddTail(element);
}

void CDataArray::SetFirstPosition(){
	if (m_elementList.IsEmpty()){
		m_pos = NULL;
	}
	m_pos = m_elementList.GetHeadPosition();
}

CDataElement* CDataArray::GetNext(){
	if (m_pos != NULL){
		return (CDataElement*)m_elementList.GetNext(m_pos);
	}
	return NULL;
}

bool CDataArray::HasNext(){
	return m_pos != NULL;
}

void CDataArray::SetTemperature(double temperature){
	m_temperature = temperature;
}
double CDataArray::GetTemperature(){
	return m_temperature;
}

void CDataArray::SetNumberOfAveraging(int averaging){
	m_averaging = averaging;
}
int CDataArray::GetNumberOfAveraging(){
	return m_averaging;
}

void CDataArray::SetTime(CTime* time){
	m_time = time;
}
CTime *CDataArray::GetTime(){
	return m_time;
}

void CDataArray::SetBoontonRange(int range){
	m_boontonRange = range;
}
int CDataArray::GetBoontonRange(){
	return m_boontonRange;
}

void CDataArray::Serialize(CArchive &ar)
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

		ar << m_temperature;
		// version 1.3
		ar << m_averaging;
		ar << count;
		SetFirstPosition();
		while (HasNext()){
			CDataElement* dataElement = GetNext();
			ar << dataElement;
		}

	} else {
		float fileVersion;
		ar >> fileVersion;
		int count;
		ar >> m_temperature;
		if (fileVersion >= 1.3f){
			ar >> m_averaging;
		} else {
			m_averaging = -1;
		}
		ar >> count;
		for (int i = 0; i < count; i++){
			CDataElement* dataElement;
			ar >> dataElement;
			this->AddElement(dataElement);
		}
		
		//this->SetOffset(count);
	}
}



void CDataArray::SetOffset(int size)
{
	int index = 0;
	int count = 0;
	
	double sum = 0.0;
	SetFirstPosition();
	int limit = floor(2 * (size/3) );
	while (HasNext()){
		CDataElement* dataElement = GetNext();
		if (index > limit){
			sum += dataElement->getValue(); 
			count++;
		}
		index++;
	}
	

	double offset = sum / count;
	SetFirstPosition();
	while (HasNext()){
		CDataElement* dataElement = GetNext();
 		 double value = dataElement->getValue() - offset; 
		 dataElement->setValue(value);
	}
}
