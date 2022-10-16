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
// C Runtime Library(CRT)提供了_ASSERT、_ASSERTE两种形式的断言，位于<crtdbg.h>头文件中。
// _ASSERT、_ASSERTE函数仅在_DEBUG宏定义的情况下有效，这也是vs的debug版本中预定义宏_DEBUG的作用。
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

// 窗口基类
class DUILIB_API CWindowWnd
{
public:
    CWindowWnd();
    // 把一个成员函数声明为const可以保证这个成员函数不修改数据成员，但是，如果数据成员是指针，则const成员函数并不能保证不修改指针指向的对象，编译器不会把这种修改检测为错误
    HWND GetHWND() const;           // 获取窗口句柄
    operator HWND() const;

    bool RegisterWindowClass();     // 注册窗口类
    bool RegisterSuperclass();

    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
    HWND CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName,DWORD dwStyle =0, DWORD dwExStyle =0);
    HWND Subclass(HWND hWnd);
    void Unsubclass();
    void ShowWindow(bool bShow = true, bool bTakeFocus = true);  // 展示窗口
    UINT ShowModal();   //  展示模态窗口
    void Close(UINT nRet = IDOK);
    void CenterWindow();	// 居中，支持扩展屏幕
    void SetIcon(UINT nRes);   // 设置任务栏图标

    LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);   // 阻塞式发送消息
    LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);   // 
    void ResizeClient(int cx = -1, int cy = -1);   // 重置客户区大小

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
