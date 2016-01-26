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

// ChildView.h : interface of the CChildView class
//


#pragma once

#include "Signals.h"

// CChildView window
class CClientHandler;

class CChildView 
	: public CWnd
	, CefMessageRouterBrowserSide::Handler
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

private:
#pragma region CefMessageRouterBrowserSide::Handler methods
	virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback) override;
	virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id) override;
#pragma endregion CefMessageRouterBrowserSide::Handler methods

	// Generated message map functions
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	CefRefPtr<CefBrowser> m_browser;
	CefRefPtr<CClientHandler> m_client;

private:
	DECLARE_MESSAGE_MAP()
	CSize GetClientSize()const;
	void SetBrowserWindowSize(int width, int height);

	afx_msg void OnDestroy();
	afx_msg void OnChangeColor();


	signals::scoped_connection m_onCreateConnection;

	bool m_colorButtonEnabled = true;
public:
	afx_msg void OnUpdateChangeColor(CCmdUI *pCmdUI);
};

