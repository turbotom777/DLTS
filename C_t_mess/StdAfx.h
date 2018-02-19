// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__732A4725_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_STDAFX_H__732A4725_A20F_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#include "Writer.h"
#include "afxtempl.h"

extern CWriter console;


#define DAQ_NO_TRANSFER_IN_PROGRESS_ERROR -10608
#define DAQ_NO_ERROR 0

const int TIMEBASE_INDEX = 1;		// 1: timebase 1 MHz
									// 2: timebase 10 kHz
									// ... see NIDAQ docu




// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__732A4725_A20F_11D9_8F79_00E0290686A0__INCLUDED_)
