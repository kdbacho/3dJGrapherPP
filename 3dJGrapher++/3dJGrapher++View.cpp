
// 3dJGrapher++View.cpp : implementation of the CMy3dJGrapherView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "3dJGrapher++.h"
#endif

#include "3dJGrapher++Doc.h"
#include "3dJGrapher++View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3dJGrapherView

IMPLEMENT_DYNCREATE(CMy3dJGrapherView, CView)

BEGIN_MESSAGE_MAP(CMy3dJGrapherView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3dJGrapherView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy3dJGrapherView construction/destruction

CMy3dJGrapherView::CMy3dJGrapherView()
{
	// TODO: add construction code here

}

CMy3dJGrapherView::~CMy3dJGrapherView()
{
}

BOOL CMy3dJGrapherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy3dJGrapherView drawing

void CMy3dJGrapherView::OnDraw(CDC* /*pDC*/)
{
	CMy3dJGrapherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMy3dJGrapherView printing


void CMy3dJGrapherView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3dJGrapherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3dJGrapherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3dJGrapherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMy3dJGrapherView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3dJGrapherView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3dJGrapherView diagnostics

#ifdef _DEBUG
void CMy3dJGrapherView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3dJGrapherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3dJGrapherDoc* CMy3dJGrapherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3dJGrapherDoc)));
	return (CMy3dJGrapherDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3dJGrapherView message handlers
