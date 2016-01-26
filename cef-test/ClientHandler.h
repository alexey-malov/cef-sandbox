#pragma once



class CClientHandler 
	: public CefClient
	, CefLifeSpanHandler
	, CefRequestHandler
{
public:
	typedef boost::signals2::signal<void(const CefRefPtr<CefBrowser> & browser)> OnBrowserCreated;

	CClientHandler();

	CefRefPtr<CefMessageRouterBrowserSide> GetMessageRouter()const;

	boost::signals2::connection DoOnBrowserCreated(const OnBrowserCreated::slot_type & handler);

private:
#pragma region CefClient methods
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override;
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
#pragma endregion CefClient methods

#pragma region CefLifeSpanHandler methods
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
#pragma endregion CefLifeSpanHandler methods

#pragma region CefRequestHandler methods
	virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status) override;
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_redirect) override;
#pragma endregion CefRequestHandler methods

	OnBrowserCreated m_onBrowserCreated;

	CefRefPtr<CefMessageRouterBrowserSide> m_messageRouter;
	IMPLEMENT_REFCOUNTING(CClientHandler);






};

