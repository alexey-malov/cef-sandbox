#pragma once
class CBrowserProcessHandler : public CefBrowserProcessHandler
{
public:
	CBrowserProcessHandler();
	~CBrowserProcessHandler();
private:
	IMPLEMENT_REFCOUNTING(CBrowserProcessHandler);
};

