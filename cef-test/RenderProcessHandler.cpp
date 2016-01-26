#include "stdafx.h"
#include "RenderProcessHandler.h"


CRenderProcessHandler::CRenderProcessHandler()
	: m_messageRouter(CefMessageRouterRendererSide::Create(CefMessageRouterConfig()))
{
}

CRenderProcessHandler::~CRenderProcessHandler()
{
}

void CRenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	m_messageRouter->OnContextCreated(browser, frame, context);
}

void CRenderProcessHandler::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	m_messageRouter->OnContextReleased(browser, frame, context);
}

bool CRenderProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	return m_messageRouter->OnProcessMessageReceived(browser, source_process, message);
}
