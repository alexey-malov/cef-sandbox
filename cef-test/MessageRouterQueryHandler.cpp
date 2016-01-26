#include "stdafx.h"
#include "MessageRouterQueryHandler.h"


CMessageRouterQueryHandler::CMessageRouterQueryHandler(QueryHandler queryHandler, QueryCancelledHandler queryCancelledHandler)
	: m_queryHandler(std::move(queryHandler))
	, m_queryCancelledHandler(std::move(queryCancelledHandler))
{
}

CMessageRouterQueryHandler::~CMessageRouterQueryHandler()
{
}

bool CMessageRouterQueryHandler::OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id, const CefString& request, bool persistent, CefRefPtr<Callback> callback)
{
	return m_queryHandler && m_queryHandler(browser, frame, query_id, request, persistent, callback);
}

void CMessageRouterQueryHandler::OnQueryCanceled(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id)
{
	if (m_queryCancelledHandler)
	{
		m_queryCancelledHandler(browser, frame, query_id);
	}
}
