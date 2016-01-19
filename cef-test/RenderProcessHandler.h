#pragma once

class CRenderProcessHandler :
	public CefRenderProcessHandler
{
public:
	CRenderProcessHandler();
	~CRenderProcessHandler();
private:
	IMPLEMENT_REFCOUNTING(CRenderProcessHandler);
};

