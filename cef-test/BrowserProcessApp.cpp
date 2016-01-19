#include "stdafx.h"
#include "BrowserProcessApp.h"
#include "BrowserProcessHandler.h"
#include "CefUtils.h"

CBrowserProcessApp::CBrowserProcessApp()
	: CBaseApp(MakeCefRefPtr<CBrowserProcessHandler>(), nullptr)
{
}

