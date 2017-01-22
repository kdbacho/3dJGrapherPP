
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ClassView.h"
#include "OutputWnd.h"

#if !defined(AFX_MAINFRM_H__582ED1C6_BB0C_48E4_9514_5116E08C9072__INCLUDED_)
#define AFX_MAINFRM_H__582ED1C6_BB0C_48E4_9514_5116E08C9072__INCLUDED_
#pragma once

class CMainFrame : public CFrameWnd
{
protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CMainFrame();
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_DYNCREATE(CMainFrame)
public:
	virtual ~CMainFrame();
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif


