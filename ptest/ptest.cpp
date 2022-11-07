#include "ptest.h"
int sindex = 0;
void PTEST::OnClick(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (sCtrlName == _T("changeBkColor"))
	{
		showMyappMsg = RegisterWindowMessage(L"MYAPP_SHOW");
		//MessageBox(m_hWnd, L"WM_NCPAINT", L"消息", MB_OK);
		DWORD dwRecipients = BSM_APPLICATIONS;
		string* msgdata = new string("qwert");
		BroadcastSystemMessage(BSF_POSTMESSAGE, &dwRecipients, showMyappMsg, NULL, NULL);
		//if (sindex++ > 3)
		//{
		//	Close();
		//	PostQuitMessage(0);
		//}
		m_bBkColor = !m_bBkColor;
		if (m_bBkColor)
		{
			bk->SetBkColor(0xffffffff);
			//Sleep(5000);
			//RECT rect;
			//GetWindowRect(m_hWnd, &rect);
			//MoveWindow(m_hWnd, 500, 100, rect.right - rect.left, rect.bottom - rect.top, true);
		}
		else
		{
			bk->SetBkColor(0xff000000);
		}
	}
}

LRESULT PTEST::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WindowImplBase::OnCreate(uMsg, wParam, lParam, bHandled);

	ShowWindow(true);
	bk = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(L"bk"));
	//SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 320,380, SWP_FRAMECHANGED);
	//UpdateLayeredWindow();
	MoveWindow(m_hWnd, 1920, 0, 50, 50, true);
	return S_OK;
}

LRESULT PTEST::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	// 测试标题栏大小改变消息
	case WM_NCCALCSIZE:
	{
		//MessageBox(m_hWnd, L"WM_NCCALCSIZE", L"消息", MB_OK);
		break;
	}
	//case WM_NCHITTEST:
	//{
	//	break;
	//}
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps = { 0 };
	//	::BeginPaint(m_hWnd, &ps);
	//	::EndPaint(m_hWnd, &ps);
	//	bHandled = TRUE;
	//	break;
	//}
	case WM_NCPAINT:
	{
		//MessageBox(m_hWnd, L"WM_NCPAINT", L"消息", MB_OK);
		break;
	}
	default:
		bHandled = FALSE;
		break;
	}
	if (!bHandled) return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT	PTEST::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd_wnd = (HWND)wParam;
	int hwndint = (int)hwnd_wnd;
	CWindowWnd* pThisc = reinterpret_cast<CWindowWnd*>(::GetWindowLongPtr(hwnd_wnd, GWLP_USERDATA));
	return S_OK;
}