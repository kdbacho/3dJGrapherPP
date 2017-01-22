#pragma once

#if !defined(AFX_OG_H__19707EED_D3DB_4E02_83E1_88298D4135F0__INCLUDED_)
#define AFX_OG_H__19707EED_D3DB_4E02_83E1_88298D4135F0__INCLUDED_

//#ifndef __AFXWIN_H__
//#error include 'stdafx.h' before including this file for PCH
//#endif

#include "resource.h"
#include "stdafx.h"
#include "OpenGL.h"

class COpenGLApp : public CWinApp
{
public:
	COpenGLApp();
	//{{AFX_VIRTUAL(COGApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COGApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif