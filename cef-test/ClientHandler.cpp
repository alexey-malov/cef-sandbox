#include "stdafx.h"
#include "ClientHandler.h"


CClientHandler::CClientHandler()
	: m_messageRouter(CefMessageRouterBrowserSide::Create(CefMessageRouterConfig()))
{
}

CefRefPtr<CefMessageRouterBrowserSide> CClientHandler::GetMessageRouter() const
{
	return m_messageRouter;
}

boost::signals2::connection CClientHandler::DoOnBrowserCreated(const OnBrowserCreated::slot_type & handler)
{
	return m_onBrowserCreated.connect(handler);
}


#pragma region CefClient methods
//////////////////////////////////////////////////////////////////////////
CefRefPtr<CefLifeSpanHandler> CClientHandler::GetLifeSpanHandler()
{
	return this;
}

CefRefPtr<CefRequestHandler> CClientHandler::GetRequestHandler()
{
	return this;
}

bool CClientHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	return m_messageRouter->OnProcessMessageReceived(browser, source_process, message);
}
//////////////////////////////////////////////////////////////////////////
#pragma endregion CefClient methods


#pragma region CefLifeSpanHandler methods
//////////////////////////////////////////////////////////////////////////
void CClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	m_onBrowserCreated(browser);
}

void CClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	m_messageRouter->OnBeforeClose(browser);
}
//////////////////////////////////////////////////////////////////////////
#pragma endregion CefLifeSpanHandler methods


#pragma region CefRequestHandler methods
//////////////////////////////////////////////////////////////////////////
void CClientHandler::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus /*status*/)
{
	m_messageRouter->OnRenderProcessTerminated(browser);
}

bool CClientHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> /*request*/, bool /*is_redirect*/)
{
	m_messageRouter->OnBeforeBrowse(browser, frame);
	return false;
}
//////////////////////////////////////////////////////////////////////////
#pragma endregion CefRequestHandler methods

