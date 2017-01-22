
// 3dJGrapher++Doc.cpp : implementation of the CMy3dJGrapherDoc class
//


#include "stdafx.h"
#include "3dJGrapher++.h"
#include "3dJGrapher++Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COGDoc

IMPLEMENT_DYNCREATE(COpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(COGDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGDoc construction/destruction

COpenGLDoc::COpenGLDoc()
{
}

COpenGLDoc::~COpenGLDoc()
{
}

BOOL COpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COGDoc serialization

void COpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// COGDoc diagnostics

#ifdef _DEBUG
void COpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGDoc commands
