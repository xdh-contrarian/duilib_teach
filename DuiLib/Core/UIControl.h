#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//

// 回调函数指针，类型名省去了，CALLBACK 只是调用约定
typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);
// VC中默认调用是 __cdecl 方式，Windows API 使用 __stdcall 调用方式，在 DLL 导出函数中，为了跟 Windows API 保持一致，建议使用 __stdcall 方式。
// __stdcall 是 StandardCall 的缩写，是C++的标准调用方式。在Microsoft C++系列的C/C++编译器中，使用 PASCAL 宏，WINAPI 宏和 CALLBACK 宏来指定函数的调用方式为 stdcall。
// __cdecl 是C Declaration的缩写（declaration，声明），cdecl调用方式又称为C调用方式，是C语言缺省的调用方式。
// 
// __stdcall
// （1）参数从右向左依次压入堆栈.
// （2）由被调用函数自己来恢复堆栈，称为自动清栈。
// （3）函数名自动加前导下划线，后面紧跟着一个@，其后紧跟着参数的大小。

// __cdecl
// （1）参数从右向左依次压入堆栈.
// （2）由调用者恢复堆栈，称为手动清栈。
// （3）函数名自动加前导下划线。


class DUILIB_API CControlUI
{
public:
    CControlUI();
    virtual void Delete();                                          // 从控件管理器中删除这个控件

protected:
    virtual ~CControlUI();

public:
    virtual CDuiString GetName() const;                             // 获取控件名字
    virtual void SetName(LPCTSTR pstrName);                         // 设置控件名字
    virtual LPCTSTR GetClass() const;                               // 控件名称
    virtual LPVOID GetInterface(LPCTSTR pstrName);                  // 通过名称获取控件实例
    virtual UINT GetControlFlags() const;
	virtual HWND GetNativeWindow() const;

    virtual bool Activate();                                        // 是否激活
    virtual CPaintManagerUI* GetManager() const;                    // 获取界面显示消息管理类实例
    virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);     // 关联消息管理类，与父组件
    virtual CControlUI* GetParent() const;                          // 获取父控件实例
    virtual CControlUI* GetCover() const;
    virtual void SetCover(CControlUI *pControl);

    // 文本相关
    virtual CDuiString GetText() const;                             // 获取文本
    virtual void SetText(LPCTSTR pstrText);

    // 图形相关
    DWORD GetBkColor() const;
    void SetBkColor(DWORD dwBackColor);
    DWORD GetBkColor2() const;
    void SetBkColor2(DWORD dwBackColor);
    DWORD GetBkColor3() const;
    void SetBkColor3(DWORD dwBackColor);
    LPCTSTR GetBkImage();
    void SetBkImage(LPCTSTR pStrImage);
	DWORD GetFocusBorderColor() const;                              // 获取聚焦时边框颜色
	void SetFocusBorderColor(DWORD dwBorderColor);
    bool IsColorHSL() const;
    void SetColorHSL(bool bColorHSL);
    SIZE GetBorderRound() const;
    void SetBorderRound(SIZE cxyRound);
    bool DrawImage(HDC hDC, TDrawInfo& drawInfo);                   // 绘制图片

	//边框相关
	DWORD GetBorderColor() const;                                   // 获取边框颜色
	void SetBorderColor(DWORD dwBorderColor);                       // 设置边框颜色
	RECT GetBorderSize() const;                                     // 获取边框大小
	void SetBorderSize(RECT rc);                                    // 设置边框大小 RECT
	void SetBorderSize(int iSize);                                  // 所有边框长度都等于这个参数
	int GetBorderStyle() const;                                     // 获取边框样式
	void SetBorderStyle(int nStyle);                                // 设置边框样式

    // 位置相关
    virtual const RECT& GetPos() const;                             // 获取位置

	virtual RECT GetRelativePos() const;                            // 获取相对于(父控件)位置
	virtual RECT GetClientPos() const;                              // 客户区域（除去scrollbar和inset）

	// 只有控件为float的时候，外部调用SetPos和Move才是有效的，位置参数是相对父控件的位置
    virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
	virtual void Move(SIZE szOffset, bool bNeedInvalidate = true);
    virtual int GetWidth() const;            // 宽
    virtual int GetHeight() const;           // 高
    virtual int GetX() const;                // 获取X坐标
    virtual int GetY() const;                // 获取Y坐标
    virtual RECT GetPadding() const;         // 获取外边距
    virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
    virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedXY(SIZE szXY);      // 仅float为true时有效
	virtual TPercentInfo GetFloatPercent() const;
	virtual void SetFloatPercent(TPercentInfo piFloatPercent);
    virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedWidth(int cx);      // 设置预设的参考宽度
    virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedHeight(int cy);     // 设置预设的参考高度
    virtual int GetMinWidth() const;         // 获取最小宽度
    virtual void SetMinWidth(int cx);        // 设置最小宽度
    virtual int GetMaxWidth() const;         // 获取最大宽度
    virtual void SetMaxWidth(int cx);        // 设置最大宽度
    virtual int GetMinHeight() const;        // 获取最小高度
    virtual void SetMinHeight(int cy);       // 设置最小高度
    virtual int GetMaxHeight() const;        // 设置最大宽度
    virtual void SetMaxHeight(int cy);       // 设置最大宽度

    // 鼠标提示
    virtual CDuiString GetToolTip() const;
    virtual void SetToolTip(LPCTSTR pstrText);
	virtual void SetToolTipWidth(int nWidth);
	virtual int	  GetToolTipWidth(void);	// 多行ToolTip单行最长宽度

    // 快捷键
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut(TCHAR ch);

    // 菜单
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed(bool bMenuUsed);

    // 用户属性
    virtual const CDuiString& GetUserData();            // 辅助函数，供用户使用
    virtual void SetUserData(LPCTSTR pstrText);         // 辅助函数，供用户使用
    virtual UINT_PTR GetTag() const;                    // 辅助函数，供用户使用
    virtual void SetTag(UINT_PTR pTag);                 // 辅助函数，供用户使用

    // 一些重要的属性
    virtual bool IsVisible() const;                     
    virtual void SetVisible(bool bVisible = true);
    virtual void SetInternVisible(bool bVisible = true); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    virtual bool IsEnabled() const;                      // 是否可以响应用户操作
    virtual void SetEnabled(bool bEnable = true);        // 设置是否响应用户操作
    virtual bool IsMouseEnabled() const;                 // 是否可以响应鼠标操作
    virtual void SetMouseEnabled(bool bEnable = true);   // 设置是否响应鼠标操作
    virtual bool IsKeyboardEnabled() const;              
    virtual void SetKeyboardEnabled(bool bEnable = true);
    virtual bool IsFocused() const;
    virtual void SetFocus();                             // 设置焦点
    virtual bool IsFloat() const;
    virtual void SetFloat(bool bFloat = true);

	// 自定义(未处理的)属性
	void AddCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
	LPCTSTR GetCustomAttribute(LPCTSTR pstrName) const;
	bool RemoveCustomAttribute(LPCTSTR pstrName);
	void RemoveAllCustomAttribute();

    virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

    void Invalidate();
    bool IsUpdateNeeded() const;
    void NeedUpdate();
    void NeedParentUpdate();
    DWORD GetAdjustColor(DWORD dwColor);

    virtual void Init();
    virtual void DoInit();

    virtual void Event(TEventUI& event);                                            // 控件相应事件
    virtual void DoEvent(TEventUI& event);

    virtual CDuiString GetAttribute(LPCTSTR pstrName);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual CDuiString GetAttributeList(bool bIgnoreDefault = true);
    virtual void SetAttributeList(LPCTSTR pstrList);

    virtual SIZE EstimateSize(SIZE szAvailable);                                    // 计算控件的宽高，不同的控件大多计算方法不同

	virtual bool Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl=NULL);// 返回要不要继续绘制
    virtual bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
    virtual void PaintBkColor(HDC hDC);                                             // 绘制背景颜色
    virtual void PaintBkImage(HDC hDC);                                             // 绘制背景图片
    virtual void PaintStatusImage(HDC hDC);
    virtual void PaintText(HDC hDC);                                                // 绘制多行文本
    virtual void PaintBorder(HDC hDC);                                              // 绘制边框

    virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

	//虚拟窗口参数
	void SetVirtualWnd(LPCTSTR pstrValue);
	CDuiString GetVirtualWnd() const;

public:
    CEventSource OnInit;
    CEventSource OnDestroy;
    CEventSource OnSize;
    CEventSource OnEvent;
    CEventSource OnNotify;
	CEventSource OnPaint;
	CEventSource OnPostPaint;

protected:
    CPaintManagerUI* m_pManager;                            // 界面显示、消息管理类
    CControlUI* m_pParent;                                  // 父控件
    CControlUI* m_pCover;                                   // 
	CDuiString m_sVirtualWnd;                               // 虚窗口
    CDuiString m_sName;                                     // 控件名字
    bool m_bUpdateNeeded;                                   // 是否需要更新            
    bool m_bMenuUsed;
	bool m_bAsyncNotify;
    RECT m_rcItem;                                          // 控件位置
    RECT m_rcPadding;                                       // 控件填充
    SIZE m_cXY;
    SIZE m_cxyFixed;
    SIZE m_cxyMin;
    SIZE m_cxyMax;
    bool m_bVisible;                                        // 是否可见
    bool m_bInternVisible;
    bool m_bEnabled;                                        // 是否可以响应用户操作
    bool m_bMouseEnabled;                                   // 是否可以响应鼠标操作
	bool m_bKeyboardEnabled ;
    bool m_bFocused;                                        // 是否具有焦点
    bool m_bFloat;                                          // 是否是相对布局
	TPercentInfo m_piFloatPercent;
    bool m_bSetPos;                                         // 防止SetPos循环调用

    CDuiString m_sText;                                     // 控件显示的文本
    CDuiString m_sToolTip;
    TCHAR m_chShortcut;
    CDuiString m_sUserData;                                 // 用户自定义文本数据
    UINT_PTR m_pTag;                                        // 用户自定义指针

    DWORD m_dwBackColor;                                    // 背景颜色
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    TDrawInfo m_diBk;
	TDrawInfo m_diFore;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
    bool m_bColorHSL;
	int m_nBorderStyle;
	int m_nTooltipWidth;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;
	RECT m_rcBorderSize;
	CDuiStringPtrMap m_mCustomAttrHash;
};

} // namespace DuiLib

#endif // __UICONTROL_H__
