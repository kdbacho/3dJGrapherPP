
#if !defined(AFX_OGVIEW_H__882A98B6_F913_424C_A692_EA5E21EFB28E__INCLUDED_)
#define AFX_OGVIEW_H__882A98B6_F913_424C_A692_EA5E21EFB28E__INCLUDED_
#pragma once
#include "ViewTree.h"
#include "3dJGrapher++Doc.h"
#include "3dJGrapher++.h"

class CPropDlg;

class CPointR3
{
public:
		float x, y, z;

	CPointR3()
	{
		x = y = z = 0;
	}

	CPointR3(float x1, float z1, float y1)
	{
		x = x1;
		y = y1;
		z = z1;
	}

	CPointR3& operator = (const CPointR3 pt)
	{
		x = pt.x;
		y = pt.y;
		z = pt.z;

		return *this;
	}

	CPointR3(const CPointR3& pt)
	{
		*this = pt;
	}
};

class COpenGLView : public CView
{
protected:
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)
public:
	long backCol; //Background Color
	HGLRC cont; //Rendering context
	HDC  dcont; //Device context
	GLenum fillmode;

	GLfloat theta_x; //Rotation angle x
	GLfloat theta_y; //Rotation angle y
	GLfloat theta_per; //Perspective
	GLfloat range_x; //x dimension
	GLfloat range_y; //y dimension
	GLfloat range_z; //z dimension
	GLfloat dx; //Infinitesimal x
	GLfloat dy; //Infinitesimal y
	GLfloat shift_x; //x displacement
	GLfloat shift_y; //y displacement
	GLfloat shift_z; //z displacement

	bool clicked;
	bool right;
	bool quad; //GL_QUAD flag

	CPoint mouse_pos;
	UINT x_size;
	UINT z_size;

	vector<CPointR3> points;
	int m_Lighting[11];
	CPropDlg *mdlg;

	COpenGLDoc* GetDocument()
	{
		return DYNAMIC_DOWNCAST(COpenGLDoc, m_pDocument);
	}
	virtual ~COpenGLView();

	void DrawScene();
	void DefaultGraphic();
	void ReadData();
	
	bool Read(HANDLE file);

	void SetGraphPoints(BYTE* buff, DWORD size);
	void SetLighting(short l, int pos);
	void GetAllLighting(int *pos);
	void SetLight();
	void SetBackgroundColor();
	void RestrictAngles();

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
protected:
	//{{AFX_MSG(COGView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnViewQuad();
	afx_msg void OnUpdateViewQuad(CCmdUI* pCmdUI);
	afx_msg void OnViewFill();
	afx_msg void OnUpdateViewFill(CCmdUI* pCmdUI);
	afx_msg void OnEditProp();
	afx_msg void OnEditBackground();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif