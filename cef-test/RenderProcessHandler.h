#pragma once

class CRenderProcessHandler 
	: public CefRenderProcessHandler
{
public:
	CRenderProcessHandler();
	~CRenderProcessHandler();
private:
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;


	CefRefPtr<CefMessageRouterRendererSide> m_messageRouter;

	IMPLEMENT_REFCOUNTING(CRenderProcessHandler);

};

