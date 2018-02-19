// HardwareException.h: interface for the CHardwareException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDWAREEXCEPTION_H__9C28C995_57BB_41EB_BE60_3D239BDB67DD__INCLUDED_)
#define AFX_HARDWAREEXCEPTION_H__9C28C995_57BB_41EB_BE60_3D239BDB67DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHardwareException  
{
public:
	CHardwareException();
	virtual ~CHardwareException();
	void setMessage(CString message);
	CString getMessage();
protected:
	CString m_message;
	
};

#endif // !defined(AFX_HARDWAREEXCEPTION_H__9C28C995_57BB_41EB_BE60_3D239BDB67DD__INCLUDED_)
