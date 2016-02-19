#include "stdafx.h"
#include "MainApp.h"
#include "ChildView.h"
#include "ClientHandler.h"
#include "CefUtils.h"
#include <boost\filesystem\path.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_CHANGE_COLOR, &CChildView::OnChangeColor)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_COLOR, &CChildView::OnUpdateChangeColor)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_client = MakeCefRefPtr<CClientHandler>();
	m_client->GetMessageRouter()->AddHandler(this, false);

	CefWindowInfo winInfo;
	CRect rc;
	GetClientRect(rc);
	winInfo.SetAsChild(m_hWnd, rc);

	WCHAR buf[MAX_PATH];
	GetModuleFileNameW(NULL, buf, MAX_PATH);
	//CefString url((boost::filesystem::path(buf).parent_path() / "index.html").native());
	CefString url(LR"(\\glitcher\wwwroot\ilyas\!keyboard\index.html)");
	
	
	m_browser = CefBrowserHost::CreateBrowserSync(winInfo, m_client, url, CefBrowserSettings(), nullptr);

	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	SetBrowserWindowSize(cx, cy);
}

CSize CChildView::GetClientSize() const
{
	CRect rc;
	GetClientRect(rc);
	return {rc.Width(), rc.Height()};
}

void CChildView::SetBrowserWindowSize(int width, int height)
{
	if (m_browser)
	{
		::SetWindowPos(m_browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, SWP_NOZORDER);
	}
}

void CChildView::OnDestroy()
{
	CWnd::OnDestroy();

	m_client->GetMessageRouter()->RemoveHandler(this);
	m_browser = nullptr;
	m_client = nullptr;
}

void CChildView::OnChangeColor()
{
	m_browser->GetMainFrame()->ExecuteJavaScript("changeColor('green');", "index.html", 0);
}

void CChildView::OnUpdateChangeColor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_colorButtonEnabled);
}


#pragma region CefMessageRouterBrowserSide::Handler methods
bool CChildView::OnQuery(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/, int64 /*query_id*/, const CefString& request, bool /*persistent*/, CefRefPtr<Callback> callback)
{
	if (request == "enableButton")
	{
		m_colorButtonEnabled = true;
		callback->Success("OK");
		return true;
	}
	else if (request == "disableButton")
	{
		m_colorButtonEnabled = false;
		callback->Success("OK");
		return true;
	}
	return false;
}

void CChildView::OnQueryCanceled(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/, int64 /*query_id*/)
{
}
#pragma endregion CefMessageRouterBrowserSide::Handler methods


