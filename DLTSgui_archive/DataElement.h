// DataElement.h: interface for the CDataElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAELEMENT_H__1CF545A8_7272_4142_85F8_7059931FF4B7__INCLUDED_)
#define AFX_DATAELEMENT_H__1CF545A8_7272_4142_85F8_7059931FF4B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataElement  : public CObject
{
public:
	void setValue(double value);
	CDataElement();
	CDataElement(double value, int time);
	virtual ~CDataElement();
	double getValue();
	int getTime();
	virtual void Serialize(CArchive& ar);


protected:
	double m_value;
	int m_time;

	DECLARE_SERIAL( CDataElement )
};

#endif // !defined(AFX_DATAELEMENT_H__1CF545A8_7272_4142_85F8_7059931FF4B7__INCLUDED_)
