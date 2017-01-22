
// 3dJGrapher++.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "3dJGrapher++.h"
#include "MainFrm.h"

#include "3dJGrapher++Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(COpenGLApp, CWinApp)
	//{{AFX_MSG_MAP(COGApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

COpenGLApp::COpenGLApp() {}
COpenGLApp theApp;

BOOL COpenGLApp::InitInstance()
{
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COpenGLDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(COpenGLView));
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

void COpenGLApp::OnAppAbout()
{
	CDialog(IDD_ABOUTBOX).DoModal();
}



