// HardwareException.cpp: implementation of the CHardwareException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HardwareException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHardwareException::CHardwareException(){

}

CHardwareException::~CHardwareException(){

}

void CHardwareException::setMessage(CString message){
	m_message = message;
}

CString CHardwareException::getMessage(){
	return m_message;
}
