#include "stdafx.h"
#include "BaseApp.h"

namespace
{
	static const CefString SINGLE_PROCESS_SWITCH_NAME = "single-process";
	static const CefString TYPE_SWITCH_NAME = "type";
	static const CefString TYPE_RENDERER = "renderer";
	static const CefString TYPE_BROWSER = "";
}

CBaseApp::CBaseApp(const CefRefPtr<CefBrowserProcessHandler> & browserProcessHandler, const CefRefPtr<CefRenderProcessHandler> & renderProcessHandler)
	: m_browserProcessHandler(browserProcessHandler)
	, m_renderProcessHandler(renderProcessHandler)
{

}

CBaseApp::ProcessType CBaseApp::GetProcessType(const CefRefPtr<CefCommandLine> & cmdLine)
{
	auto type = cmdLine->GetSwitchValue(TYPE_SWITCH_NAME);
	return cmdLine->HasSwitch(SINGLE_PROCESS_SWITCH_NAME) ? ProcessType::SingleProcess :
		(type == TYPE_RENDERER) ? ProcessType::Renderer :
		(type == TYPE_BROWSER) ? ProcessType::Browser : 
		ProcessType::Other;
}

CefRefPtr<CefBrowserProcessHandler> CBaseApp::GetBrowserProcessHandler()
{
	return m_browserProcessHandler;
}

CefRefPtr<CefRenderProcessHandler> CBaseApp::GetRenderProcessHandler()
{
	return m_renderProcessHandler;
}
