// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// cef-test.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MainApp.h"
#include "MainFrm.h"
#include "BaseApp.h"
#include "BrowserProcessHandler.h"
#include "RenderProcessHandler.h"
#include "CefUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CMainApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMainApp::OnAppAbout)
END_MESSAGE_MAP()

CMainApp::CMainApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("cef-test.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CBrowserApp object

CMainApp theApp;


// CBrowserApp initialization

BOOL CMainApp::InitInstance()
{
	auto cmdLine = CefCommandLine::CreateCommandLine();
	cmdLine->InitFromString(::GetCommandLineW());
	auto processType = CBaseApp::GetProcessType(cmdLine);

	CefRefPtr<CefBrowserProcessHandler> browserProcessHandler;
	CefRefPtr<CefRenderProcessHandler> renderProcessHandler;
	switch (processType)
	{
	case CBaseApp::ProcessType::SingleProcess:
		browserProcessHandler = MakeCefRefPtr<CBrowserProcessHandler>();
		renderProcessHandler = MakeCefRefPtr<CRenderProcessHandler>();
		break;
	case CBaseApp::ProcessType::Browser:
		browserProcessHandler = MakeCefRefPtr<CBrowserProcessHandler>();
		break;
	case CBaseApp::ProcessType::Renderer:
		renderProcessHandler = MakeCefRefPtr<CRenderProcessHandler>();
		break;
	case CBaseApp::ProcessType::Other:
		break;
	default:
		break;
	}

	InitControls();

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltips();

	return SetupMainWindow();
}

BOOL CMainApp::SetupMainWindow()
{
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

void CMainApp::InitTooltips()
{
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
}

void CMainApp::InitControls()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
}

int CMainApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CBrowserApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMainApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CBrowserApp customization load/save methods

void CMainApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMainApp::LoadCustomState()
{
}

void CMainApp::SaveCustomState()
{
}

// CBrowserApp message handlers



