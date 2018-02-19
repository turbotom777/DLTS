// DataArray.h: interface for the CDataArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAARRAY_H__1E9B00CF_5C72_46B0_A6ED_25B194F4DB4B__INCLUDED_)
#define AFX_DATAARRAY_H__1E9B00CF_5C72_46B0_A6ED_25B194F4DB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataElement;

class CDataArray : public CObject 
{
public:
	CDataArray();
	virtual ~CDataArray();

	void AddElement(CDataElement *element);
	void SetFirstPosition();
	CDataElement* GetNext();
	bool HasNext();

	virtual void Serialize(CArchive& ar);

	void SetTemperature(double temperature);
	double GetTemperature();
	void SetNumberOfAveraging(int average);
	int GetNumberOfAveraging();
	void SetTime(CTime* time);
	CTime *GetTime();
	void SetBoontonRange(int range);
	int GetBoontonRange();

protected:
	void SetOffset(int size);
	double m_temperature;
	int m_averaging;
	CTime *m_time;
	int m_boontonRange;
	CPtrList m_elementList;
	POSITION m_pos;

	DECLARE_SERIAL( CDataArray )
};

#endif // !defined(AFX_DATAARRAY_H__1E9B00CF_5C72_46B0_A6ED_25B194F4DB4B__INCLUDED_)
