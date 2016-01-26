#include "stdafx.h"
#include "RenderProcessApp.h"
#include "RenderProcessHandler.h"
#include "CefUtils.h"


CRenderProcessApp::CRenderProcessApp()
	: CBaseApp(nullptr, MakeCefRefPtr<CRenderProcessHandler>())
{
}


CRenderProcessApp::~CRenderProcessApp()
{
}
