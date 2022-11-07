#ifndef __UILABEL_H__
#define __UILABEL_H__

#pragma once

#define _USE_GDIPLUS 1

#ifdef _USE_GDIPLUS
#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;
class DUILIB_API Gdiplus::RectF;
struct DUILIB_API Gdiplus::GdiplusStartupInput;
#endif


namespace DuiLib
{
	class DUILIB_API CLabelUI : public CControlUI
	{
	public:
		CLabelUI();
		~CLabelUI();

		LPCTSTR GetClass() const;						// 获取控件名称
		LPVOID GetInterface(LPCTSTR pstrName);			// 根据控件名称获取控件指针

        void SetFixedWidth(int cx);						// 设置预设宽度
        void SetFixedHeight(int cy);					// 设置预设高度
		void SetText(LPCTSTR pstrText);					// 设置字体

		void SetTextStyle(UINT uStyle);					// 设置字体样式
		UINT GetTextStyle() const;						// 获取字体样式
		bool IsMultiLine();								// 是否多行text
		void SetMultiLine(bool bMultiLine = true);		// 设置多行
		void SetTextColor(DWORD dwTextColor);			// 设置字体颜色
		DWORD GetTextColor() const;						// 获取字体颜色
		void SetDisabledTextColor(DWORD dwTextColor);	// 设置失效状态字体颜色
		DWORD GetDisabledTextColor() const;				// 获取失效状态字体颜色
		void SetFont(int index);						// 设置 字体
		int GetFont() const;							// 获取 字体 id
		RECT GetTextPadding() const;					// 获取 字体 padding
		void SetTextPadding(RECT rc);					// 设置 字体 padding
		bool IsShowHtml();								// 是否展示 html
		void SetShowHtml(bool bShowHtml = true);		// 设置 是 html

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);								// 执行事件
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);		// 设置 属性

		void PaintText(HDC hDC);									// 绘制字体

#ifdef _USE_GDIPLUS
		void		SetEnabledEffect(bool _EnabledEffect);
		bool		GetEnabledEffect();
		void		SetEnabledLuminous(bool bEnableLuminous);
		bool		GetEnabledLuminous();
		void		SetLuminousFuzzy(float fFuzzy);
		float		GetLuminousFuzzy();
		void		SetGradientLength(int _GradientLength);
		int			GetGradientLength();
		void		SetShadowOffset(int _offset,int _angle);
		RectF		GetShadowOffset();
		void		SetTextColor1(DWORD _TextColor1);				// 设置字体颜色
		DWORD		GetTextColor1();								// 获取字体颜色
		void		SetTextShadowColorA(DWORD _TextShadowColorA);
		DWORD		GetTextShadowColorA();
		void		SetTextShadowColorB(DWORD _TextShadowColorB);
		DWORD		GetTextShadowColorB();
		void		SetStrokeColor(DWORD _StrokeColor);
		DWORD		GetStrokeColor();
		void		SetGradientAngle(int _SetGradientAngle);
		int			GetGradientAngle();
		void		SetEnabledStroke(bool _EnabledStroke);
		bool		GetEnabledStroke();
		void		SetEnabledShadow(bool _EnabledShadowe);
		bool		GetEnabledShadow();
#endif
	
	protected:
		LPWSTR  m_pWideText;				// 字体宽字节格式
		DWORD	m_dwTextColor;				// 字体颜色
		DWORD	m_dwDisabledTextColor;		// 失效状态字体颜色
		int		m_iFont;					// 字体 id
		UINT	m_uTextStyle;				// 字体 样式
		RECT	m_rcTextPadding;			// 字体 填充
		bool	m_bShowHtml;				// 是否展示 html
        SIZE    m_szAvailableLast;
        SIZE    m_cxyFixedLast;
        bool    m_bNeedEstimateSize;

		float					m_fLuminousFuzzy;
		int						m_GradientLength;
		int						m_GradientAngle;
		bool					m_EnableEffect;
		bool					m_bEnableLuminous;
		bool					m_EnabledStroke;
		bool					m_EnabledShadow;
		DWORD					m_dwTextColor1;
		DWORD					m_dwTextShadowColorA;
		DWORD					m_dwTextShadowColorB;
		DWORD					m_dwStrokeColor;
		RectF					m_ShadowOffset;
		ULONG_PTR				m_gdiplusToken;
#ifdef _USE_GDIPLUS
		GdiplusStartupInput		m_gdiplusStartupInput;
#endif
	};
}

#endif // __UILABEL_H__