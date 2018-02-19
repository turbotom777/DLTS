// DataElement.cpp: implementation of the CDataElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dltsgui.h"
#include "DataElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDataElement, CObject, 1)


CDataElement::CDataElement()
{
	m_value = 0;
	m_time = 0;
}

CDataElement::CDataElement(double value, int time)
{
	m_value = value;
	m_time = time;
}

CDataElement::~CDataElement()
{
}
double CDataElement::getValue(){
	return m_value;
}
int CDataElement::getTime(){
	return m_time;
}

void CDataElement::Serialize(CArchive &ar)
{
	CObject::Serialize( ar ); 
	
	if (ar.IsStoring()){
		float fileVersion = FILE_VERSION;
		ar << fileVersion;
		ar << m_time;
		ar << m_value;
	} else {
		float fileVersion;
		ar >> fileVersion;
		ar >> m_time;
		ar >> m_value;
	}
}


void CDataElement::setValue(double value)
{
	m_value = value;
}
