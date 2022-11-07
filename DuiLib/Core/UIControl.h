#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//

// �ص�����ָ�룬������ʡȥ�ˣ�CALLBACK ֻ�ǵ���Լ��
typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);
// VC��Ĭ�ϵ����� __cdecl ��ʽ��Windows API ʹ�� __stdcall ���÷�ʽ���� DLL ���������У�Ϊ�˸� Windows API ����һ�£�����ʹ�� __stdcall ��ʽ��
// __stdcall �� StandardCall ����д����C++�ı�׼���÷�ʽ����Microsoft C++ϵ�е�C/C++�������У�ʹ�� PASCAL �꣬WINAPI ��� CALLBACK ����ָ�������ĵ��÷�ʽΪ stdcall��
// __cdecl ��C Declaration����д��declaration����������cdecl���÷�ʽ�ֳ�ΪC���÷�ʽ����C����ȱʡ�ĵ��÷�ʽ��
// 
// __stdcall
// ��1������������������ѹ���ջ.
// ��2���ɱ����ú����Լ����ָ���ջ����Ϊ�Զ���ջ��
// ��3���������Զ���ǰ���»��ߣ����������һ��@���������Ų����Ĵ�С��

// __cdecl
// ��1������������������ѹ���ջ.
// ��2���ɵ����߻ָ���ջ����Ϊ�ֶ���ջ��
// ��3���������Զ���ǰ���»��ߡ�


class DUILIB_API CControlUI
{
public:
    CControlUI();
    virtual void Delete();                                          // �ӿؼ���������ɾ������ؼ�

protected:
    virtual ~CControlUI();

public:
    virtual CDuiString GetName() const;                             // ��ȡ�ؼ�����
    virtual void SetName(LPCTSTR pstrName);                         // ���ÿؼ�����
    virtual LPCTSTR GetClass() const;                               // �ؼ�����
    virtual LPVOID GetInterface(LPCTSTR pstrName);                  // ͨ�����ƻ�ȡ�ؼ�ʵ��
    virtual UINT GetControlFlags() const;
	virtual HWND GetNativeWindow() const;

    virtual bool Activate();                                        // �Ƿ񼤻�
    virtual CPaintManagerUI* GetManager() const;                    // ��ȡ������ʾ��Ϣ������ʵ��
    virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);     // ������Ϣ�����࣬�븸���
    virtual CControlUI* GetParent() const;                          // ��ȡ���ؼ�ʵ��
    virtual CControlUI* GetCover() const;
    virtual void SetCover(CControlUI *pControl);

    // �ı����
    virtual CDuiString GetText() const;                             // ��ȡ�ı�
    virtual void SetText(LPCTSTR pstrText);

    // ͼ�����
    DWORD GetBkColor() const;
    void SetBkColor(DWORD dwBackColor);
    DWORD GetBkColor2() const;
    void SetBkColor2(DWORD dwBackColor);
    DWORD GetBkColor3() const;
    void SetBkColor3(DWORD dwBackColor);
    LPCTSTR GetBkImage();
    void SetBkImage(LPCTSTR pStrImage);
	DWORD GetFocusBorderColor() const;                              // ��ȡ�۽�ʱ�߿���ɫ
	void SetFocusBorderColor(DWORD dwBorderColor);
    bool IsColorHSL() const;
    void SetColorHSL(bool bColorHSL);
    SIZE GetBorderRound() const;
    void SetBorderRound(SIZE cxyRound);
    bool DrawImage(HDC hDC, TDrawInfo& drawInfo);                   // ����ͼƬ

	//�߿����
	DWORD GetBorderColor() const;                                   // ��ȡ�߿���ɫ
	void SetBorderColor(DWORD dwBorderColor);                       // ���ñ߿���ɫ
	RECT GetBorderSize() const;                                     // ��ȡ�߿��С
	void SetBorderSize(RECT rc);                                    // ���ñ߿��С RECT
	void SetBorderSize(int iSize);                                  // ���б߿򳤶ȶ������������
	int GetBorderStyle() const;                                     // ��ȡ�߿���ʽ
	void SetBorderStyle(int nStyle);                                // ���ñ߿���ʽ

    // λ�����
    virtual const RECT& GetPos() const;                             // ��ȡλ��

	virtual RECT GetRelativePos() const;                            // ��ȡ�����(���ؼ�)λ��
	virtual RECT GetClientPos() const;                              // �ͻ����򣨳�ȥscrollbar��inset��

	// ֻ�пؼ�Ϊfloat��ʱ���ⲿ����SetPos��Move������Ч�ģ�λ�ò�������Ը��ؼ���λ��
    virtual void SetPos(RECT rc, bool bNeedInvalidate = true);
	virtual void Move(SIZE szOffset, bool bNeedInvalidate = true);
    virtual int GetWidth() const;            // ��
    virtual int GetHeight() const;           // ��
    virtual int GetX() const;                // ��ȡX����
    virtual int GetY() const;                // ��ȡY����
    virtual RECT GetPadding() const;         // ��ȡ��߾�
    virtual void SetPadding(RECT rcPadding); // ������߾࣬���ϲ㴰�ڻ���
    virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedXY(SIZE szXY);      // ��floatΪtrueʱ��Ч
	virtual TPercentInfo GetFloatPercent() const;
	virtual void SetFloatPercent(TPercentInfo piFloatPercent);
    virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedWidth(int cx);      // ����Ԥ��Ĳο����
    virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedHeight(int cy);     // ����Ԥ��Ĳο��߶�
    virtual int GetMinWidth() const;         // ��ȡ��С���
    virtual void SetMinWidth(int cx);        // ������С���
    virtual int GetMaxWidth() const;         // ��ȡ�����
    virtual void SetMaxWidth(int cx);        // ���������
    virtual int GetMinHeight() const;        // ��ȡ��С�߶�
    virtual void SetMinHeight(int cy);       // ������С�߶�
    virtual int GetMaxHeight() const;        // ���������
    virtual void SetMaxHeight(int cy);       // ���������

    // �����ʾ
    virtual CDuiString GetToolTip() const;
    virtual void SetToolTip(LPCTSTR pstrText);
	virtual void SetToolTipWidth(int nWidth);
	virtual int	  GetToolTipWidth(void);	// ����ToolTip��������

    // ��ݼ�
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut(TCHAR ch);

    // �˵�
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed(bool bMenuUsed);

    // �û�����
    virtual const CDuiString& GetUserData();            // �������������û�ʹ��
    virtual void SetUserData(LPCTSTR pstrText);         // �������������û�ʹ��
    virtual UINT_PTR GetTag() const;                    // �������������û�ʹ��
    virtual void SetTag(UINT_PTR pTag);                 // �������������û�ʹ��

    // һЩ��Ҫ������
    virtual bool IsVisible() const;                     
    virtual void SetVisible(bool bVisible = true);
    virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    virtual bool IsEnabled() const;                      // �Ƿ������Ӧ�û�����
    virtual void SetEnabled(bool bEnable = true);        // �����Ƿ���Ӧ�û�����
    virtual bool IsMouseEnabled() const;                 // �Ƿ������Ӧ������
    virtual void SetMouseEnabled(bool bEnable = true);   // �����Ƿ���Ӧ������
    virtual bool IsKeyboardEnabled() const;              
    virtual void SetKeyboardEnabled(bool bEnable = true);
    virtual bool IsFocused() const;
    virtual void SetFocus();                             // ���ý���
    virtual bool IsFloat() const;
    virtual void SetFloat(bool bFloat = true);

	// �Զ���(δ�����)����
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

    virtual void Event(TEventUI& event);                                            // �ؼ���Ӧ�¼�
    virtual void DoEvent(TEventUI& event);

    virtual CDuiString GetAttribute(LPCTSTR pstrName);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual CDuiString GetAttributeList(bool bIgnoreDefault = true);
    virtual void SetAttributeList(LPCTSTR pstrList);

    virtual SIZE EstimateSize(SIZE szAvailable);                                    // ����ؼ��Ŀ�ߣ���ͬ�Ŀؼ������㷽����ͬ

	virtual bool Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl=NULL);// ����Ҫ��Ҫ��������
    virtual bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
    virtual void PaintBkColor(HDC hDC);                                             // ���Ʊ�����ɫ
    virtual void PaintBkImage(HDC hDC);                                             // ���Ʊ���ͼƬ
    virtual void PaintStatusImage(HDC hDC);
    virtual void PaintText(HDC hDC);                                                // ���ƶ����ı�
    virtual void PaintBorder(HDC hDC);                                              // ���Ʊ߿�

    virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

	//���ⴰ�ڲ���
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
    CPaintManagerUI* m_pManager;                            // ������ʾ����Ϣ������
    CControlUI* m_pParent;                                  // ���ؼ�
    CControlUI* m_pCover;                                   // 
	CDuiString m_sVirtualWnd;                               // �鴰��
    CDuiString m_sName;                                     // �ؼ�����
    bool m_bUpdateNeeded;                                   // �Ƿ���Ҫ����            
    bool m_bMenuUsed;
	bool m_bAsyncNotify;
    RECT m_rcItem;                                          // �ؼ�λ��
    RECT m_rcPadding;                                       // �ؼ����
    SIZE m_cXY;
    SIZE m_cxyFixed;
    SIZE m_cxyMin;
    SIZE m_cxyMax;
    bool m_bVisible;                                        // �Ƿ�ɼ�
    bool m_bInternVisible;
    bool m_bEnabled;                                        // �Ƿ������Ӧ�û�����
    bool m_bMouseEnabled;                                   // �Ƿ������Ӧ������
	bool m_bKeyboardEnabled ;
    bool m_bFocused;                                        // �Ƿ���н���
    bool m_bFloat;                                          // �Ƿ�����Բ���
	TPercentInfo m_piFloatPercent;
    bool m_bSetPos;                                         // ��ֹSetPosѭ������

    CDuiString m_sText;                                     // �ؼ���ʾ���ı�
    CDuiString m_sToolTip;
    TCHAR m_chShortcut;
    CDuiString m_sUserData;                                 // �û��Զ����ı�����
    UINT_PTR m_pTag;                                        // �û��Զ���ָ��

    DWORD m_dwBackColor;                                    // ������ɫ
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
