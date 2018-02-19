// DataArrayList.h: interface for the CDataArrayList class.
//
//////////////////////////////////////////////////////////////////////



#if !defined(AFX_DATAARRAYLIST_H__6B5A5DAB_F6D4_4C22_839E_3B111B66D9E2__INCLUDED_)
#define AFX_DATAARRAYLIST_H__6B5A5DAB_F6D4_4C22_839E_3B111B66D9E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CDataArray;

class CDataArrayList  : public CObject
{
public:
	int GetItemCount();
	virtual void Serialize(CArchive& ar);
	CDataArrayList();
	virtual ~CDataArrayList();
	void AddElement(CDataArray *element);
	void SetFirstPosition();
	CDataArray* GetNext();
	bool HasNext();

protected:
	CPtrList m_elementList;
	POSITION m_pos;

	DECLARE_SERIAL( CDataArrayList )




};







#endif // !defined(AFX_DATAARRAYLIST_H__6B5A5DAB_F6D4_4C22_839E_3B111B66D9E2__INCLUDED_)

