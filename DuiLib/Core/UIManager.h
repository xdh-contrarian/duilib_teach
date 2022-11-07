#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CControlUI;


/////////////////////////////////////////////////////////////////////////////////////
//
// �¼�����
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
    HFONT hFont;                    // �߼�����ľ��
    CDuiString sFontName;           // ����ؼ�����
    int iSize;                      // �ֺŴ�С
    bool bBold;                     // �Ƿ����
    bool bUnderline;                // �Ƿ����»���
    bool bItalic;                   // �Ƿ�б��
    TEXTMETRIC tm;                  // �й���������Ļ�����Ϣ
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
	DWORD m_dwDefaultDisabledColor;                     // Ĭ��ʧЧ״̬��ɫ
	DWORD m_dwDefaultFontColor;                         // Ĭ��������ɫ
	DWORD m_dwDefaultLinkFontColor;                     // Ĭ�ϳ�����������ɫ
	DWORD m_dwDefaultLinkHoverFontColor;                // Ĭ�ϳ����������ͣ״̬��������ɫ
	DWORD m_dwDefaultSelectedBkColor;                   // Ĭ��ѡ��״̬����ɫ
	TFontInfo m_DefaultFontInfo;                        // Ĭ��������Ϣ
	CDuiStringPtrMap m_CustomFonts;                     // �Զ���������Դ����
	CDuiStringPtrMap m_ImageHash;                       // ͼƬ��ԴHashMap
	CDuiStringPtrMap m_AttrHash;                        
	CDuiStringPtrMap m_MultiLanguageHash;
} TResInfo;

// Structure for notifications from the system
// to the control implementation.
// ϵͳ֪ͨ�Ľṹ��
typedef struct DUILIB_API tagTEventUI
{
    int Type;                   // ����
    CControlUI* pSender;        // ������(�����) �ؼ�
    DWORD dwTimestamp;          // ����ʱ�� 
    POINT ptMouse;              // �������λ�� (��ǰ����)
    TCHAR chKey;
    WORD wKeyState;             // ����״̬
    WPARAM wParam;
    LPARAM lParam;
} TEventUI;

// Listener interface
class DUILIB_API INotifyUI
{
public:
    virtual void Notify(TNotifyUI& msg) = 0;                    // �ؼ���Ӧ��Ϣ�ӿ�
};

// MessageFilter interface
class DUILIB_API IMessageFilterUI
{
public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;    // ��Ϣ�������ӿ�
};

class DUILIB_API ITranslateAccelerator
{
public:
	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);

// ������ʾ����Ϣ������
class DUILIB_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

public:
    void Init(HWND hWnd, LPCTSTR pstrName = NULL);
	bool IsUpdateNeeded() const;                                    // �Ƿ���Ҫ���½���
    void NeedUpdate();                                              // ������Ҫ���½���
	void Invalidate();                                              // ˢ�½���
    void Invalidate(RECT& rcItem);                                  // ˢ��ĳ������ָ������ʧЧ

	LPCTSTR GetName() const;
    HDC GetPaintDC() const;                                         // ��ȡ ֱ�ӻ��Ƶ������DC
	HBITMAP GetPaintOffscreenBitmap();
    HWND GetPaintWindow() const;                                    // ��ȡ��ͼ�Ĵ��ھ��
    HWND GetTooltipWindow() const;
	int GetTooltipWindowWidth() const;
	void SetTooltipWindowWidth(int iWidth);
	int GetHoverTime() const;
	void SetHoverTime(int iTime);

    POINT GetMousePos() const;                                      // ��ȡ ������µ�λ��
    SIZE GetClientSize() const;
    SIZE GetInitSize();                                             // ��ȡ��ʼ���ڴ�С
    void SetInitSize(int cx, int cy);                               // ���ó�ʼ���ڴ�С
    RECT& GetSizeBox();                                             // ��ȡ����ı߿������С
    void SetSizeBox(RECT& rcSizeBox);                               // ���ô���ı߿������С
    RECT& GetCaptionRect();                                         // ��ȡ������λ��
    void SetCaptionRect(RECT& rcCaption);                           // ���ñ�����λ��
    SIZE GetRoundCorner() const;                                    // ��ȡ�����Ľǵ�Բ�ǻ���
    void SetRoundCorner(int cx, int cy);                            // ���ô����Ľǵ�Բ�ǻ���
	SIZE GetMinInfo() const;                                        // ��ȡ������Ե���������С SIZE
	void SetMinInfo(int cx, int cy);                                // ���ô�����Ե���������С SIZE
	SIZE GetMaxInfo() const;                                        // ��ȡ������Ե���������� SIZE
	void SetMaxInfo(int cx, int cy);                                // ���ô�����Ե���������� SIZE
    bool IsShowUpdateRect() const;                                  // �Ƿ���ʾ��������
    void SetShowUpdateRect(bool show);                              // �����Ƿ���ʾ��������
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

    static HINSTANCE GetInstance();                                                // ��ȡ���̾��
    static CDuiString GetInstancePath();                                           // ��ȡexe·��
    static CDuiString GetCurrentPath();
    static HINSTANCE GetResourceDll();
    static const CDuiString& GetResourcePath();                                    // ���� ��Դ��·��(��"\"��β)
    static const CDuiString& GetResourceZip();                                     // ���� Zip��Դ��·��
    static bool IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
    static void SetInstance(HINSTANCE hInst);                                       // ���ý��̾��
    static void SetCurrentPath(LPCTSTR pStrPath);
    static void SetResourceDll(HINSTANCE hInst);
    static void SetResourcePath(LPCTSTR pStrPath);                                  // ������Դ·��
	static void SetResourceZip(LPVOID pVoid, unsigned int len);                     // ������Դѹ����·��
    static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);   // ������Դѹ����·��
    static bool GetHSL(short* H, short* S, short* L);
    static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
	static CPaintManagerUI* GetPaintManager(LPCTSTR pstrName);
	static CDuiPtrArray* GetPaintManagers();                                        // ��ȡ CPaintManagerUIʵ��ָ������ 
    static bool LoadPlugin(LPCTSTR pstrModuleName);
    static CDuiPtrArray* GetPlugins();                                              // ��ȡ ��� ����

	bool IsForceUseSharedRes() const;
	void SetForceUseSharedRes(bool bForce);

    DWORD GetDefaultDisabledColor() const;                                          // ��ȡĬ��ʧЧ״̬��ɫ
    void SetDefaultDisabledColor(DWORD dwColor, bool bShared = false);              // ����Ĭ��ʧЧ״̬��ɫ
    DWORD GetDefaultFontColor() const;                                              // ��ȡĬ��������ɫ
    void SetDefaultFontColor(DWORD dwColor, bool bShared = false);                  // ��ȡĬ��������ɫ
    DWORD GetDefaultLinkFontColor() const;                                          // ��ȡ�������ֵ�Ĭ��������ɫ
    void SetDefaultLinkFontColor(DWORD dwColor, bool bShared = false);              // �����������ֵ�Ĭ��������ɫ
    DWORD GetDefaultLinkHoverFontColor() const;                                     // ��ȡ�����ͣ�볬���ϵ�Ĭ��������ɫ            
    void SetDefaultLinkHoverFontColor(DWORD dwColor, bool bShared = false);         // ���������ͣ�볬���ϵ�Ĭ��������ɫ
    DWORD GetDefaultSelectedBkColor() const;                                        // ��ȡѡ��״̬��Ĭ�ϱ�����ɫ
    void SetDefaultSelectedBkColor(DWORD dwColor, bool bShared = false);            // ����ѡ��״̬��Ĭ�ϱ�����ɫ

    TFontInfo* GetDefaultFontInfo();                                                                                            // ��ȡĬ��ʹ�õ�������Ϣ
    void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);      // ����Ĭ��ʹ�õ�������Ϣ
    DWORD GetCustomFontCount(bool bShared = false) const;
    HFONT AddFont(int id, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);    // �������
    HFONT GetFont(int id);                                                                                                      // ͨ������ id ��ȡ������
    HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	int GetFontIndex(HFONT hFont, bool bShared = false);
	int GetFontIndex(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bShared = false);
    void RemoveFont(HFONT hFont, bool bShared = false);
    void RemoveFont(int id, bool bShared = false);
    void RemoveAllFonts(bool bShared = false);
    TFontInfo* GetFontInfo(int id);                                                                                             // ͨ������id ��ȡ������Ϣ
    TFontInfo* GetFontInfo(HFONT hFont);                                                                                        // ͨ�������� ��ȡ������Ϣ

    const TImageInfo* GetImage(LPCTSTR bitmap);                                                                                 // ����ͼ��·������ͼ����Ϣ
    const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false);                    // ��������,���ͣ�����ɫ ��ѯͼ����Ϣ
    const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bUseHSL = false, bool bShared = false);// ���ͼ��
    const TImageInfo* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha, bool bShared = false);
    void RemoveImage(LPCTSTR bitmap, bool bShared = false);
    void RemoveAllImages(bool bShared = false);
	static void ReloadSharedImages();
	void ReloadImages();

    void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList, bool bShared = false);   // ��ӿؼ�Ĭ������
    LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;                    // ���ݿؼ����Ʋ�ѯ����ؼ���Ĭ������
    bool RemoveDefaultAttributeList(LPCTSTR pStrControlName, bool bShared = false);
    void RemoveAllDefaultAttributeList(bool bShared = false);

    void AddWindowCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
    LPCTSTR GetWindowCustomAttribute(LPCTSTR pstrName) const;
    bool RemoveWindowCustomAttribute(LPCTSTR pstrName);
    void RemoveAllWindowCustomAttribute();

    CDuiString GetWindowAttribute(LPCTSTR pstrName);
    void SetWindowAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);               // ���ô�������
    CDuiString GetWindowAttributeList(bool bIgnoreDefault = true);
    void SetWindowAttributeList(LPCTSTR pstrList);
    bool RemoveWindowAttribute(LPCTSTR pstrName);

    CDuiString GetWindowXML();

	static void AddMultiLanguageString(int id, LPCTSTR pStrMultiLanguage);
	static LPCTSTR GetMultiLanguageString(int id);
	static bool RemoveMultiLanguageString(int id);
	static void RemoveAllMultiLanguageString();
	static void ProcessMultiLanguageTokens(CDuiString& pStrMultiLanguage);

    bool AttachDialog(CControlUI* pControl);                                    // ���ؼ�����Ϊ ��Ԫ��
    bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);        // ��ʼ��һ���ؼ�ʵ��
	bool RenameControl(CControlUI* pControl, LPCTSTR pstrName);                 // �������ؼ�����
    void ReapObjects(CControlUI* pControl);

    bool AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);           // ��ӿؼ���ָ����ѡ����
    CDuiPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);                        // ͨ�� ѡ���� �����ֲ���ѡ����
    void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    void RemoveAllOptionGroups();

    CControlUI* GetFocus() const;                                               // ��ȡ ��ǰ���н���Ŀؼ�
    void SetFocus(CControlUI* pControl, bool bFocusWnd=true);                   // ���õ�ǰ�����ڵ�ǰ�ؼ���
    void SetFocusNeeded(CControlUI* pControl);

    bool SetNextTabControl(bool bForward = true);                              // ������һ�����Tab�����ý���Ŀؼ���Tab�Ƿ����������

    bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
    bool KillTimer(CControlUI* pControl, UINT nTimerID);
    void KillTimer(CControlUI* pControl);
    void RemoveAllTimers();

    void SetCapture();                                                          // ���ô����������¼�
    void ReleaseCapture();                                                      // �ͷŴ�����겶��
    bool IsCaptured();                                                          // �Ƿ���Ҫ֧����겶��

	bool IsPainting();
	void SetPainting(bool bIsPainting);

    bool AddNotifier(INotifyUI* pControl);                                      // ��� ��Ӧ��Ϣ֪ͨ��
    bool RemoveNotifier(INotifyUI* pControl);                                   // �Ƴ� ��Ӧ��Ϣ֪ͨ��
    void SendNotify(TNotifyUI& Msg, bool bAsync = false, bool bEnableRepeat = true); // ����ͬ��/�첽֪ͨ
    void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false, bool bEnableRepeat = true); // ����ͬ�����첽֪ͨ������

    bool AddPreMessageFilter(IMessageFilterUI* pFilter);                       // �����Ϣ������
    bool RemovePreMessageFilter(IMessageFilterUI* pFilter);                    // �Ƴ���Ϣ������

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
    void AddMouseLeaveNeeded(CControlUI* pControl);                                 // ��ӵ��ؼ���������
    bool RemoveMouseLeaveNeeded(CControlUI* pControl);                              // ���ݿؼ�ָ��ӹ�������ɾ������ؼ�

	bool AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool TranslateAccelerator(LPMSG pMsg);

    CControlUI* GetRoot() const;                                                    // ���� ���ڵ�ؼ�
    CControlUI* FindControl(POINT pt) const;                                        // ���� ���� ��λ�ò��ҿؼ�
    CControlUI* FindControl(LPCTSTR pstrName) const;                                // ͨ���ؼ����� �ڿؼ�hash���в��ҿؼ�
    CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
    CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
    CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
    CDuiPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);

    static void MessageLoop();                                                          // ��Ϣѭ��
    static bool TranslateMessage(const LPMSG pMsg);                                     // ������Ϣ
	static void Term();

    bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);        // ��Ϣ������ת����
    bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);     // Ԥ�ȴ�����Ϣ��
	void UsedVirtualWnd(bool bUsed);                                                    // ���� �Ƿ�ʹ���鴰��

private:
	CDuiPtrArray* GetFoundControls();                                                               // ��ȡ��Ҫ���µĿؼ�����
    static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);         // �����еĿؼ���ӵ�m_mNameHash��ϣ����
    static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);            // ����ؼ�����
    static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);            // ���ݵ��Ƿ��������У���ѯ�ؼ�
    static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);              // ͨ��Tab��Ϣ��ѯ�ؼ�
    static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);         // �ӿ����в�ѯ�ؼ�
    static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);             // ͨ�����ƱȽϲ�ѯ�ؼ�
    static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);            
    static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);           
	static CControlUI* CALLBACK __FindControlsFromUpdate(CControlUI* pThis, LPVOID pData);          // ������Ҫ���µĿؼ�

	static void AdjustSharedImagesHSL();
	void AdjustImagesHSL();
	void PostAsyncNotify();                                                                         // �����첽��Ϣ

private:
	CDuiString m_sName;                                         // 
    HWND m_hWndPaint;                                           // ����Direct��ͼ�����Ĵ�����
    HDC m_hDcPaint;                                             // ֱ�ӻ��Ƶ������DC(Ϊ�����������������ǿͻ���)
    HDC m_hDcOffscreen;                                         // �ڴ滺������ͼDC
    HDC m_hDcBackground;                                        // ��������(֧��AlphaBackgroundʱʹ��)
    HBITMAP m_hbmpOffscreen;                                    // m_hDcPaint�ĺ�̨��ͼ����
	COLORREF* m_pOffscreenBits;                                 
    HBITMAP m_hbmpBackground;                                   // ����ͼƬbmp
	COLORREF* m_pBackgroundBits;
	int m_iTooltipWidth;            
    int m_iLastTooltipWidth;
	HWND m_hwndTooltip;                                         // ��ʾ���ھ��
	TOOLINFO m_ToolTip;                                         // ��ʾ��Ϣ
	int m_iHoverTime;
    bool m_bNoActivate;
    bool m_bShowUpdateRect;                                     // �Ƿ���ʾ��������
    //
    CControlUI* m_pRoot;                                        // xml���ڵ�����ɵĶ���ͨ��Ϊ����Window
    CControlUI* m_pFocus;                                       // ���ڻ�ý���״̬�Ŀؼ�
    CControlUI* m_pEventHover;                                  // ���������ͣ״̬�Ŀؼ�
    CControlUI* m_pEventClick;                                  // ��������Ŀؼ�
    CControlUI* m_pEventKey;                                    // ���ռ�������Ŀؼ�
    CControlUI* m_pLastToolTip;
    //
    POINT m_ptLastMousePos;                                     // ������µ�λ��
    SIZE m_szMinWindow;                                         // ������Ե���������С SIZE
    SIZE m_szMaxWindow;                                         // ������Ե���������� SIZE
    SIZE m_szInitWindowSize;                                    // �����ʼ��ʱ�Ĵ�С
    RECT m_rcSizeBox;                                           // ������߿�����Ĵ�С
    SIZE m_szRoundCorner;                                       // �����Ľǵ�Բ�ǻ���
    RECT m_rcCaption;                                           // �������������λ��
    UINT m_uTimerID;                                            // ��ǰ��ʱ��ID
    bool m_bFirstLayout;                                        // �Ƿ����׸�����
    bool m_bUpdateNeeded;                                       // �Ƿ���Ҫ���½���
    bool m_bFocusNeeded;                                        // �Ƿ���Ҫ����
    bool m_bOffscreenPaint;                                     // �Ƿ���Ҫ��˫�����ͼ

	BYTE m_nOpacity;
	bool m_bLayered;                                            // �Ƿ����͸������
	RECT m_rcLayeredInset;
	bool m_bLayeredChanged;
	RECT m_rcLayeredUpdate;
	TDrawInfo m_diLayered;

    bool m_bMouseTracking;                                      // �Ƿ���Ҫ֧�����׷��
    bool m_bMouseCapture;                                       // �Ƿ���Ҫ֧����겶��
	bool m_bIsPainting;                                         // 
	bool m_bUsedVirtualWnd;                                     // �Ƿ�ʹ�õ��鴰��
	bool m_bAsyncNotifyPosted;                                  // �첽��Ϣ�Ƿ��Ѿ�����

    // ��������Ϣ
    CDuiPtrArray m_aNotifiers;                                  // �ܹ�����֪ͨ�Ķ��󼯺�
    CDuiPtrArray m_aTimers;                                     // ��ʱ������
    CDuiPtrArray m_aPreMessageFilters;                          // Ԥ������Ϣ����������
    CDuiPtrArray m_aMessageFilters;                             // ��Ϣ����������
    CDuiPtrArray m_aPostPaintControls;                          // ���ͻ�������Ŀؼ�����
	CDuiPtrArray m_aNativeWindow;
	CDuiPtrArray m_aNativeWindowControl;
    CDuiPtrArray m_aDelayedCleanup;                             // �ӳ�����Ķ��󼯺�
    CDuiPtrArray m_aAsyncNotify;                                // �첽֪ͨ��Ϣ����
    CDuiPtrArray m_aFoundControls;                              // ��Ҫ���µĿؼ�����
    CDuiPtrArray m_aNeedMouseLeaveNeeded;                       // �ؼ�����������װ��ָ������
    CDuiStringPtrMap m_mNameHash;                               // �ؼ�����HashMap key - �ؼ���, value - �ؼ�ָ��
	CDuiStringPtrMap m_mWindowAttrHash;
    CDuiStringPtrMap m_mOptionGroup;                            // ѡ����Map

    //
	bool m_bForceUseSharedRes;
	TResInfo m_ResInfo;                                         // ��Դ��Ϣ

    //
	static HINSTANCE m_hResourceInstance;                       // ��ǰ�������ԴDLL Instanceʵ��
	static CDuiString m_pStrResourcePath;                       // ��ǰʹ�õ���Դ·��
	static CDuiString m_pStrResourceZip;                        // ��ǰʹ�õ���Դѹ�����ļ�ȫ��
	static HANDLE m_hResourceZip;

	static bool m_bCachedResourceZip;                           // 
	static TResInfo m_SharedResInfo;                            // ������Դ��Ϣ
    static HINSTANCE m_hInstance;                               // ��ǰ�����Instanceʵ��
	static bool m_bUseHSL;
	static short m_H;
	static short m_S;
	static short m_L;
	static CDuiPtrArray m_aPreMessages;                         // CPaintManagerUIʵ��ָ������ �洢�˵�ǰ���������е�CPaintManagerUIʵ��ָ�룬����ж��CPaintManagerUIʵ���� Ҳ������ڹ������⣬�������ţ����ܸ��Թ��ˡ�
    static CDuiPtrArray m_aPlugins;                             // 

public:
	CDuiPtrArray m_aTranslateAccelerator;                       // 
};

} // namespace DuiLib

#endif // __UIMANAGER_H__
