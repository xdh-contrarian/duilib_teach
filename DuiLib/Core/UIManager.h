#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CControlUI;


/////////////////////////////////////////////////////////////////////////////////////
//
// 事件类型
typedef enum EVENTTYPE_UI
{
    UIEVENT__FIRST = 1,
    UIEVENT__KEYBEGIN,
    UIEVENT_KEYDOWN,
    UIEVENT_KEYUP,
    UIEVENT_CHAR,
    UIEVENT_SYSKEY,
    UIEVENT__KEYEND,
    UIEVENT__MOUSEBEGIN,
    UIEVENT_MOUSEMOVE,
    UIEVENT_MOUSELEAVE,
    UIEVENT_MOUSEENTER,
    UIEVENT_MOUSEHOVER,
    UIEVENT_BUTTONDOWN,
    UIEVENT_BUTTONUP,
    UIEVENT_RBUTTONDOWN,
    UIEVENT_DBLCLICK,
    UIEVENT_CONTEXTMENU,
    UIEVENT_SCROLLWHEEL,
    UIEVENT__MOUSEEND,
    UIEVENT_KILLFOCUS,
    UIEVENT_SETFOCUS,
    UIEVENT_WINDOWSIZE,
    UIEVENT_SETCURSOR,
    UIEVENT_TIMER,
    UIEVENT_NOTIFY,
    UIEVENT_COMMAND,
    UIEVENT__LAST,
};

/////////////////////////////////////////////////////////////////////////////////////
//

// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_UPDATETEST    0x00000008
#define UIFIND_TOP_FIRST     0x00000010
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040



/////////////////////////////////////////////////////////////////////////////////////
//

typedef struct DUILIB_API tagTFontInfo
{
    HFONT hFont;                    // 逻辑字体的句柄
    CDuiString sFontName;           // 字体控件名字
    int iSize;                      // 字号大小
    bool bBold;                     // 是否粗体
    bool bUnderline;                // 是否有下划线
    bool bItalic;                   // 是否斜体
    TEXTMETRIC tm;                  // 有关物理字体的基本信息
} TFontInfo;

typedef struct DUILIB_API tagTImageInfo
{
    HBITMAP hBitmap;
    LPBYTE pBits;
	LPBYTE pSrcBits;
    int nX;
    int nY;
    bool bAlpha;
    bool bUseHSL;
    CDuiString sResType;
    DWORD dwMask;
} TImageInfo;

typedef struct DUILIB_API tagTDrawInfo
{
	tagTDrawInfo();
	tagTDrawInfo(LPCTSTR lpsz);
	void Clear();
	CDuiString sDrawString;
    CDuiString sImageName;
	bool bLoaded;
	const TImageInfo* pImageInfo;
	RECT rcDestOffset;
	RECT rcBmpPart;
	RECT rcScale9;
	BYTE uFade;
	bool bHole;
	bool bTiledX;
	bool bTiledY;
} TDrawInfo;

typedef struct DUILIB_API tagTPercentInfo
{
	double left;
	double top;
	double right;
	double bottom;
} TPercentInfo;

typedef struct DUILIB_API tagTResInfo
{
	DWORD m_dwDefaultDisabledColor;                     // 默认失效状态颜色
	DWORD m_dwDefaultFontColor;                         // 默认字体颜色
	DWORD m_dwDefaultLinkFontColor;                     // 默认超链接字体颜色
	DWORD m_dwDefaultLinkHoverFontColor;                // 默认超链接鼠标悬停状态的字体颜色
	DWORD m_dwDefaultSelectedBkColor;                   // 默认选中状态背景色
	TFontInfo m_DefaultFontInfo;                        // 默认字体信息
	CDuiStringPtrMap m_CustomFonts;                     // 自定义字体资源集合
	CDuiStringPtrMap m_ImageHash;                       // 图片资源HashMap
	CDuiStringPtrMap m_AttrHash;                        
	CDuiStringPtrMap m_MultiLanguageHash;
} TResInfo;

// Structure for notifications from the system
// to the control implementation.
// 系统通知的结构体
typedef struct DUILIB_API tagTEventUI
{
    int Type;                   // 类型
    CControlUI* pSender;        // 发送者(被点击) 控件
    DWORD dwTimestamp;          // 生成时间 
    POINT ptMouse;              // 鼠标点击的位置 (当前窗口)
    TCHAR chKey;
    WORD wKeyState;             // 键盘状态
    WPARAM wParam;
    LPARAM lParam;
} TEventUI;

// Listener interface
class DUILIB_API INotifyUI
{
public:
    virtual void Notify(TNotifyUI& msg) = 0;                    // 控件响应消息接口
};

// MessageFilter interface
class DUILIB_API IMessageFilterUI
{
public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;    // 消息过滤器接口
};

class DUILIB_API ITranslateAccelerator
{
public:
	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);

// 界面显示、消息管理类
class DUILIB_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

public:
    void Init(HWND hWnd, LPCTSTR pstrName = NULL);
	bool IsUpdateNeeded() const;                                    // 是否需要更新界面
    void NeedUpdate();                                              // 设置需要更新界面
	void Invalidate();                                              // 刷新界面
    void Invalidate(RECT& rcItem);                                  // 刷新某个区域，指定区域失效

	LPCTSTR GetName() const;
    HDC GetPaintDC() const;                                         // 获取 直接绘制到窗体的DC
	HBITMAP GetPaintOffscreenBitmap();
    HWND GetPaintWindow() const;                                    // 获取绘图的窗口句柄
    HWND GetTooltipWindow() const;
	int GetTooltipWindowWidth() const;
	void SetTooltipWindowWidth(int iWidth);
	int GetHoverTime() const;
	void SetHoverTime(int iTime);

    POINT GetMousePos() const;                                      // 获取 鼠标最新的位置
    SIZE GetClientSize() const;
    SIZE GetInitSize();                                             // 获取初始窗口大小
    void SetInitSize(int cx, int cy);                               // 设置初始窗口大小
    RECT& GetSizeBox();                                             // 获取窗体的边框区域大小
    void SetSizeBox(RECT& rcSizeBox);                               // 设置窗体的边框区域大小
    RECT& GetCaptionRect();                                         // 获取标题栏位置
    void SetCaptionRect(RECT& rcCaption);                           // 设置标题栏位置
    SIZE GetRoundCorner() const;                                    // 获取窗体四角的圆角弧度
    void SetRoundCorner(int cx, int cy);                            // 设置窗体四角的圆角弧度
	SIZE GetMinInfo() const;                                        // 获取窗体可以调整到的最小 SIZE
	void SetMinInfo(int cx, int cy);                                // 设置窗体可以调整到的最小 SIZE
	SIZE GetMaxInfo() const;                                        // 获取窗体可以调整到的最大 SIZE
	void SetMaxInfo(int cx, int cy);                                // 设置窗体可以调整到的最大 SIZE
    bool IsShowUpdateRect() const;                                  // 是否显示更新区域
    void SetShowUpdateRect(bool show);                              // 设置是否显示更新区域
    bool IsNoActivate();
    void SetNoActivate(bool bNoActivate);

	BYTE GetOpacity() const;
	void SetOpacity(BYTE nOpacity);

	bool IsLayered();
	void SetLayered(bool bLayered);
	RECT& GetLayeredInset();
	void SetLayeredInset(RECT& rcLayeredInset);
	BYTE GetLayeredOpacity();
	void SetLayeredOpacity(BYTE nOpacity);
	LPCTSTR GetLayeredImage();
	void SetLayeredImage(LPCTSTR pstrImage);

    static HINSTANCE GetInstance();                                                // 获取进程句柄
    static CDuiString GetInstancePath();                                           // 获取exe路径
    static CDuiString GetCurrentPath();
    static HINSTANCE GetResourceDll();
    static const CDuiString& GetResourcePath();                                    // 返回 资源的路径(以"\"结尾)
    static const CDuiString& GetResourceZip();                                     // 返回 Zip资源的路径
    static bool IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
    static void SetInstance(HINSTANCE hInst);                                       // 设置进程句柄
    static void SetCurrentPath(LPCTSTR pStrPath);
    static void SetResourceDll(HINSTANCE hInst);
    static void SetResourcePath(LPCTSTR pStrPath);                                  // 设置资源路径
	static void SetResourceZip(LPVOID pVoid, unsigned int len);                     // 设置资源压缩包路径
    static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);   // 设置资源压缩包路径
    static bool GetHSL(short* H, short* S, short* L);
    static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
	static CPaintManagerUI* GetPaintManager(LPCTSTR pstrName);
	static CDuiPtrArray* GetPaintManagers();                                        // 获取 CPaintManagerUI实例指针数组 
    static bool LoadPlugin(LPCTSTR pstrModuleName);
    static CDuiPtrArray* GetPlugins();                                              // 获取 插件 数组

	bool IsForceUseSharedRes() const;
	void SetForceUseSharedRes(bool bForce);

    DWORD GetDefaultDisabledColor() const;                                          // 获取默认失效状态颜色
    void SetDefaultDisabledColor(DWORD dwColor, bool bShared = false);              // 设置默认失效状态颜色
    DWORD GetDefaultFontColor() const;                                              // 获取默认字体颜色
    void SetDefaultFontColor(DWORD dwColor, bool bShared = false);                  // 获取默认字体颜色
    DWORD GetDefaultLinkFontColor() const;                                          // 获取链接文字的默认字体颜色
    void SetDefaultLinkFontColor(DWORD dwColor, bool bShared = false);              // 设置链接文字的默认字体颜色
    DWORD GetDefaultLinkHoverFontColor() const;                                     // 获取鼠标悬停与超链上的默认字体颜色            
    void SetDefaultLinkHoverFontColor(DWORD dwColor, bool bShared = false);         // 设置鼠标悬停与超链上的默认字体颜色
    DWORD GetDefaultSelectedBkColor() const;                                        // 获取选中状态的默认背景颜色
    void SetDefaultSelectedBkColor(DWORD dwColor, bool bShared = false);            // 设置选中状态的默认背景颜色

    TFontInfo* GetDefaultFontInfo();                                                                                            // 获取默认使用的字体信息
    void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);      // 设置默认使用的字体信息
    DWORD GetCustomFontCount(bool bShared = false) const;
    HFONT AddFont(int id, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);    // 添加字体
    HFONT GetFont(int id);                                                                                                      // 通过字体 id 获取字体句柄
    HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	int GetFontIndex(HFONT hFont, bool bShared = false);
	int GetFontIndex(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);
    void RemoveFont(HFONT hFont, bool bShared = false);
    void RemoveFont(int id, bool bShared = false);
    void RemoveAllFonts(bool bShared = false);
    TFontInfo* GetFontInfo(int id);                                                                                             // 通过字体id 获取字体信息
    TFontInfo* GetFontInfo(HFONT hFont);                                                                                        // 通过字体句柄 获取字体信息

    const TImageInfo* GetImage(LPCTSTR bitmap);                                                                                 // 根据图像路径查找图像信息
    const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false);                    // 根据名称,类型，遮罩色 查询图像信息
    const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false, bool bShared = false);// 添加图像
    const TImageInfo* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha, bool bShared = false);
    void RemoveImage(LPCTSTR bitmap, bool bShared = false);
    void RemoveAllImages(bool bShared = false);
	static void ReloadSharedImages();
	void ReloadImages();

    void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList, bool bShared = false);   // 添加控件默认配置
    LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;                    // 根据控件名称查询该类控件的默认配置
    bool RemoveDefaultAttributeList(LPCTSTR pStrControlName, bool bShared = false);
    void RemoveAllDefaultAttributeList(bool bShared = false);

    void AddWindowCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
    LPCTSTR GetWindowCustomAttribute(LPCTSTR pstrName) const;
    bool RemoveWindowCustomAttribute(LPCTSTR pstrName);
    void RemoveAllWindowCustomAttribute();

    CDuiString GetWindowAttribute(LPCTSTR pstrName);
    void SetWindowAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);               // 设置窗口属性
    CDuiString GetWindowAttributeList(bool bIgnoreDefault = true);
    void SetWindowAttributeList(LPCTSTR pstrList);
    bool RemoveWindowAttribute(LPCTSTR pstrName);

    CDuiString GetWindowXML();

	static void AddMultiLanguageString(int id, LPCTSTR pStrMultiLanguage);
	static LPCTSTR GetMultiLanguageString(int id);
	static bool RemoveMultiLanguageString(int id);
	static void RemoveAllMultiLanguageString();
	static void ProcessMultiLanguageTokens(CDuiString& pStrMultiLanguage);

    bool AttachDialog(CControlUI* pControl);                                    // 将控件设置为 根元素
    bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);        // 初始化一个控件实例
	bool RenameControl(CControlUI* pControl, LPCTSTR pstrName);                 // 重命名控件名字
    void ReapObjects(CControlUI* pControl);

    bool AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);           // 添加控件到指定的选项组
    CDuiPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);                        // 通过 选项组 的名字查找选项组
    void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    void RemoveAllOptionGroups();

    CControlUI* GetFocus() const;                                               // 获取 当前具有焦点的控件
    void SetFocus(CControlUI* pControl, bool bFocusWnd=true);                   // 设置当前焦点在当前控件上
    void SetFocusNeeded(CControlUI* pControl);

    bool SetNextTabControl(bool bForward = true);                              // 设置下一个获得Tab键会获得焦点的控件，Tab是否继续往下走

    bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
    bool KillTimer(CControlUI* pControl, UINT nTimerID);
    void KillTimer(CControlUI* pControl);
    void RemoveAllTimers();

    void SetCapture();                                                          // 设置窗体接受鼠标事件
    void ReleaseCapture();                                                      // 释放窗体鼠标捕获
    bool IsCaptured();                                                          // 是否需要支持鼠标捕获

	bool IsPainting();
	void SetPainting(bool bIsPainting);

    bool AddNotifier(INotifyUI* pControl);                                      // 添加 响应消息通知者
    bool RemoveNotifier(INotifyUI* pControl);                                   // 移除 响应消息通知者
    void SendNotify(TNotifyUI& Msg, bool bAsync = false, bool bEnableRepeat = true); // 发送同步/异步通知
    void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false, bool bEnableRepeat = true); // 构建同步或异步通知并发送

    bool AddPreMessageFilter(IMessageFilterUI* pFilter);                       // 添加消息过滤器
    bool RemovePreMessageFilter(IMessageFilterUI* pFilter);                    // 移除消息过滤器

    bool AddMessageFilter(IMessageFilterUI* pFilter);
    bool RemoveMessageFilter(IMessageFilterUI* pFilter);

    int GetPostPaintCount() const;
    bool AddPostPaint(CControlUI* pControl);
    bool RemovePostPaint(CControlUI* pControl);
    bool SetPostPaintIndex(CControlUI* pControl, int iIndex);

	int GetNativeWindowCount() const;
	RECT GetNativeWindowRect(HWND hChildWnd);
	bool AddNativeWindow(CControlUI* pControl, HWND hChildWnd);
	bool RemoveNativeWindow(HWND hChildWnd);

    void AddDelayedCleanup(CControlUI* pControl);
    void AddMouseLeaveNeeded(CControlUI* pControl);                                 // 添加到控件管理器中
    bool RemoveMouseLeaveNeeded(CControlUI* pControl);                              // 根据控件指针从管理器中删除这个控件

	bool AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool TranslateAccelerator(LPMSG pMsg);

    CControlUI* GetRoot() const;                                                    // 返回 根节点控件
    CControlUI* FindControl(POINT pt) const;                                        // 根据 光标点 的位置查找控件
    CControlUI* FindControl(LPCTSTR pstrName) const;                                // 通过控件名字 在控件hash表中查找控件
    CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
    CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
    CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
    CDuiPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);

    static void MessageLoop();                                                          // 消息循环
    static bool TranslateMessage(const LPMSG pMsg);                                     // 翻译消息
	static void Term();

    bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);        // 消息处理中转中心
    bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);     // 预先处理消息器
	void UsedVirtualWnd(bool bUsed);                                                    // 设置 是否使用虚窗口

private:
	CDuiPtrArray* GetFoundControls();                                                               // 获取需要更新的控件集合
    static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);         // 将所有的控件添加到m_mNameHash哈希表中
    static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);            // 计算控件数量
    static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);            // 根据点是否在区域中，查询控件
    static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);              // 通过Tab信息查询控件
    static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);         // 从快照中查询控件
    static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);             // 通过名称比较查询控件
    static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);            
    static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);           
	static CControlUI* CALLBACK __FindControlsFromUpdate(CControlUI* pThis, LPVOID pData);          // 查找需要更新的控件

	static void AdjustSharedImagesHSL();
	void AdjustImagesHSL();
	void PostAsyncNotify();                                                                         // 发送异步消息

private:
	CDuiString m_sName;                                         // 
    HWND m_hWndPaint;                                           // 进行Direct绘图操作的窗体句柄
    HDC m_hDcPaint;                                             // 直接绘制到窗体的DC(为窗体的整个区域包括非客户区)
    HDC m_hDcOffscreen;                                         // 内存缓冲区绘图DC
    HDC m_hDcBackground;                                        // 背景绘制(支持AlphaBackground时使用)
    HBITMAP m_hbmpOffscreen;                                    // m_hDcPaint的后台作图画布
	COLORREF* m_pOffscreenBits;                                 
    HBITMAP m_hbmpBackground;                                   // 背景图片bmp
	COLORREF* m_pBackgroundBits;
	int m_iTooltipWidth;            
    int m_iLastTooltipWidth;
	HWND m_hwndTooltip;                                         // 提示窗口句柄
	TOOLINFO m_ToolTip;                                         // 提示消息
	int m_iHoverTime;
    bool m_bNoActivate;
    bool m_bShowUpdateRect;                                     // 是否显示更新区域
    //
    CControlUI* m_pRoot;                                        // xml根节点解析成的对象，通常为各种Window
    CControlUI* m_pFocus;                                       // 处于获得焦点状态的控件
    CControlUI* m_pEventHover;                                  // 处于鼠标悬停状态的控件
    CControlUI* m_pEventClick;                                  // 被鼠标点击的控件
    CControlUI* m_pEventKey;                                    // 接收键盘输入的控件
    CControlUI* m_pLastToolTip;
    //
    POINT m_ptLastMousePos;                                     // 鼠标最新的位置
    SIZE m_szMinWindow;                                         // 窗体可以调整到的最小 SIZE
    SIZE m_szMaxWindow;                                         // 窗体可以调整到的最大 SIZE
    SIZE m_szInitWindowSize;                                    // 窗体初始化时的大小
    RECT m_rcSizeBox;                                           // 窗体外边框区域的大小
    SIZE m_szRoundCorner;                                       // 窗体四角的圆角弧度
    RECT m_rcCaption;                                           // 窗体标题栏区域位置
    UINT m_uTimerID;                                            // 当前定时器ID
    bool m_bFirstLayout;                                        // 是否是首个布局
    bool m_bUpdateNeeded;                                       // 是否需要更新界面
    bool m_bFocusNeeded;                                        // 是否需要焦点
    bool m_bOffscreenPaint;                                     // 是否需要开双缓存绘图

	BYTE m_nOpacity;
	bool m_bLayered;                                            // 是否具有透明属性
	RECT m_rcLayeredInset;
	bool m_bLayeredChanged;
	RECT m_rcLayeredUpdate;
	TDrawInfo m_diLayered;

    bool m_bMouseTracking;                                      // 是否需要支持鼠标追踪
    bool m_bMouseCapture;                                       // 是否需要支持鼠标捕获
	bool m_bIsPainting;                                         // 
	bool m_bUsedVirtualWnd;                                     // 是否使用的虚窗口
	bool m_bAsyncNotifyPosted;                                  // 异步消息是否已经发送

    // 集合类信息
    CDuiPtrArray m_aNotifiers;                                  // 能够接收通知的对象集合
    CDuiPtrArray m_aTimers;                                     // 定时器集合
    CDuiPtrArray m_aPreMessageFilters;                          // 预处理消息过滤器集合
    CDuiPtrArray m_aMessageFilters;                             // 消息过滤器集合
    CDuiPtrArray m_aPostPaintControls;                          // 发送绘制请求的控件集合
	CDuiPtrArray m_aNativeWindow;
	CDuiPtrArray m_aNativeWindowControl;
    CDuiPtrArray m_aDelayedCleanup;                             // 延迟清理的对象集合
    CDuiPtrArray m_aAsyncNotify;                                // 异步通知消息集合
    CDuiPtrArray m_aFoundControls;                              // 需要更新的控件集合
    CDuiPtrArray m_aNeedMouseLeaveNeeded;                       // 控件管理器，封装的指针数组
    CDuiStringPtrMap m_mNameHash;                               // 控件名称HashMap key - 控件名, value - 控件指针
	CDuiStringPtrMap m_mWindowAttrHash;
    CDuiStringPtrMap m_mOptionGroup;                            // 选项组Map

    //
	bool m_bForceUseSharedRes;
	TResInfo m_ResInfo;                                         // 资源信息

    //
	static HINSTANCE m_hResourceInstance;                       // 当前管理的资源DLL Instance实例
	static CDuiString m_pStrResourcePath;                       // 当前使用的资源路径
	static CDuiString m_pStrResourceZip;                        // 当前使用的资源压缩包文件全称
	static HANDLE m_hResourceZip;

	static bool m_bCachedResourceZip;                           // 
	static TResInfo m_SharedResInfo;                            // 共享资源信息
    static HINSTANCE m_hInstance;                               // 当前管理的Instance实例
	static bool m_bUseHSL;
	static short m_H;
	static short m_S;
	static short m_L;
	static CDuiPtrArray m_aPreMessages;                         // CPaintManagerUI实例指针数组 存储了当前进程中所有的CPaintManagerUI实例指针，如果有多个CPaintManagerUI实例， 也不会存在过滤问题，互不干扰，都能各自过滤。
    static CDuiPtrArray m_aPlugins;                             // 

public:
	CDuiPtrArray m_aTranslateAccelerator;                       // 
};

} // namespace DuiLib

#endif // __UIMANAGER_H__
