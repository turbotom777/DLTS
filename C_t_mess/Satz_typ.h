// Satz_typ.h: interface for the Satz_typ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SATZ_TYP_H__7961196B_A74C_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_SATZ_TYP_H__7961196B_A74C_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSatz_typ  
{
public:
	CSatz_typ();
	virtual ~CSatz_typ();


	int Satznummer;
    double Temperatur;
    int abstand;
    double matrix[128];
    int FEHLER [20];
};

#endif // !defined(AFX_SATZ_TYP_H__7961196B_A74C_11D9_8F79_00E0290686A0__INCLUDED_)
