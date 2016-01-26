#include "stdafx.h"
#include "SingleProcessApp.h"
#include "BrowserProcessHandler.h"
#include "CefUtils.h"
#include "RenderProcessHandler.h"


CSingleProcessApp::CSingleProcessApp()
	: CBaseApp(MakeCefRefPtr<CBrowserProcessHandler>(), MakeCefRefPtr<CRenderProcessHandler>())
{
}

CSingleProcessApp::~CSingleProcessApp()
{
}
