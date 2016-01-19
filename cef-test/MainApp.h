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

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


class CMainApp : public CWinAppEx
{
public:
	CMainApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	BOOL SetupMainWindow();
	void InitTooltips();
	void InitControls();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMainApp theApp;
