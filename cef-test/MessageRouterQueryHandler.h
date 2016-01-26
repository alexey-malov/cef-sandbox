#pragma once
class CMessageRouterQueryHandler 
	: public CefMessageRouterBrowserSide::Handler
	, boost::noncopyable
{
public:
	typedef std::function<bool(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback)> QueryHandler;
	typedef std::function<void(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id)> QueryCancelledHandler;
	CMessageRouterQueryHandler(QueryHandler queryHandler, QueryCancelledHandler queryCancelledHandler);
	~CMessageRouterQueryHandler();
private:
	virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback) override;
	virtual void OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id) override;

	QueryHandler m_queryHandler;
	QueryCancelledHandler m_queryCancelledHandler;

};

