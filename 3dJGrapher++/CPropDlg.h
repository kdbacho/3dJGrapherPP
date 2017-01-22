#pragma once
#if !defined(AFX_PROPDLG_H__9CBD8D0A_BCA5_4F0F_A7D1_A37F51824158__INCLUDED_)
#define AFX_PROPDLG_H__9CBD8D0A_BCA5_4F0F_A7D1_A37F51824158__INCLUDED_

#include "stdafx.h"

class COGView;

class CPropDlg : public CDialog
{
public:
	COpenGLView *m_pView;
	int m_Pos[11];

	CPropDlg(COpenGLView* p);
	int GetSliderNum(HWND hwnd, UINT& nID);


	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_PROP };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPropDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPropDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnFilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif