// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8FD28334_DD94_42E3_8B3A_0BA51E9F0844__INCLUDED_)
#define AFX_STDAFX_H__8FD28334_DD94_42E3_8B3A_0BA51E9F0844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls

// for CList
#include <afxtempl.h>


#include "resource.h"
#include "Afxcview.h"

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <iostream>

// global definitions
#include "Writer.h"
extern CWriter console;

#include "DltsConstants.h"
#include "DLTSdevice.h"


extern CDLTSdevice* GetDltsDevice();


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8FD28334_DD94_42E3_8B3A_0BA51E9F0844__INCLUDED_)
