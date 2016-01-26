#pragma once

class CBaseApp :
	public CefApp
{
public:
	enum class ProcessType
	{
		SingleProcess,
		Browser,
		Renderer,
		Other,
	};

	CBaseApp(const CefRefPtr<CefBrowserProcessHandler> & browserProcessHandler = nullptr, const CefRefPtr<CefRenderProcessHandler> & renderProcessHandler = nullptr);

	static ProcessType GetProcessType(const CefRefPtr<CefCommandLine> & cmdLine);

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override final;

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override final;

private:
	const CefRefPtr<CefBrowserProcessHandler> m_browserProcessHandler;
	const CefRefPtr<CefRenderProcessHandler> m_renderProcessHandler;

	IMPLEMENT_REFCOUNTING(CBaseApp);
};

