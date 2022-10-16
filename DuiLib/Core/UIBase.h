#ifndef __UIBASE_H__
#define __UIBASE_H__


#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//
// C Runtime Library(CRT)�ṩ��_ASSERT��_ASSERTE������ʽ�Ķ��ԣ�λ��<crtdbg.h>ͷ�ļ��С�
// _ASSERT��_ASSERTE��������_DEBUG�궨����������Ч����Ҳ��vs��debug�汾��Ԥ�����_DEBUG�����á�
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr) 
#endif

#ifdef _DEBUG
#ifndef DUITRACE
#define DUITRACE DUI__Trace
#endif
#define DUITRACEMSG DUI__TraceMsg
#else
#ifndef DUITRACE
#define DUITRACE
#endif
#define DUITRACEMSG _T("")
#endif

void DUILIB_API DUI__Trace(LPCTSTR pstrFormat, ...);
LPCTSTR DUILIB_API DUI__TraceMsg(UINT uMsg);

/////////////////////////////////////////////////////////////////////////////////////
//

class DUILIB_API CNotifyPump
{
public:
	bool AddVirtualWnd(CDuiString strName,CNotifyPump* pObject);
	bool RemoveVirtualWnd(CDuiString strName);
	void NotifyPump(TNotifyUI& msg);
	bool LoopDispatch(TNotifyUI& msg);
	DUI_DECLARE_MESSAGE_MAP()
private:
	CDuiStringPtrMap m_VirtualWndMap;
};

// ���ڻ���
class DUILIB_API CWindowWnd
{
public:
    CWindowWnd();
    // ��һ����Ա��������Ϊconst���Ա�֤�����Ա�������޸����ݳ�Ա�����ǣ�������ݳ�Ա��ָ�룬��const��Ա���������ܱ�֤���޸�ָ��ָ��Ķ��󣬱���������������޸ļ��Ϊ����
    HWND GetHWND() const;           // ��ȡ���ھ��
    operator HWND() const;

    bool RegisterWindowClass();     // ע�ᴰ����
    bool RegisterSuperclass();

    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
    HWND CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName,DWORD dwStyle =0, DWORD dwExStyle =0);
    HWND Subclass(HWND hWnd);
    void Unsubclass();
    void ShowWindow(bool bShow = true, bool bTakeFocus = true);  // չʾ����
    UINT ShowModal();   //  չʾģ̬����
    void Close(UINT nRet = IDOK);
    void CenterWindow();	// ���У�֧����չ��Ļ
    void SetIcon(UINT nRes);   // ����������ͼ��

    LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);   // ����ʽ������Ϣ
    LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);   // 
    void ResizeClient(int cx = -1, int cy = -1);   // ���ÿͻ�����С

protected:
    virtual LPCTSTR GetWindowClassName() const = 0;
    virtual LPCTSTR GetSuperClassName() const;
    virtual UINT GetClassStyle() const;

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void OnFinalMessage(HWND hWnd);

    static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    HWND m_hWnd;
    WNDPROC m_OldWndProc;
    bool m_bSubclassed;
};

} // namespace DuiLib

#endif // __UIBASE_H__
