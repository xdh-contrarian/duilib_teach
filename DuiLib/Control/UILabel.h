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

		LPCTSTR GetClass() const;						// ��ȡ�ؼ�����
		LPVOID GetInterface(LPCTSTR pstrName);			// ���ݿؼ����ƻ�ȡ�ؼ�ָ��

        void SetFixedWidth(int cx);						// ����Ԥ����
        void SetFixedHeight(int cy);					// ����Ԥ��߶�
		void SetText(LPCTSTR pstrText);					// ��������

		void SetTextStyle(UINT uStyle);					// ����������ʽ
		UINT GetTextStyle() const;						// ��ȡ������ʽ
		bool IsMultiLine();								// �Ƿ����text
		void SetMultiLine(bool bMultiLine = true);		// ���ö���
		void SetTextColor(DWORD dwTextColor);			// ����������ɫ
		DWORD GetTextColor() const;						// ��ȡ������ɫ
		void SetDisabledTextColor(DWORD dwTextColor);	// ����ʧЧ״̬������ɫ
		DWORD GetDisabledTextColor() const;				// ��ȡʧЧ״̬������ɫ
		void SetFont(int index);						// ���� ����
		int GetFont() const;							// ��ȡ ���� id
		RECT GetTextPadding() const;					// ��ȡ ���� padding
		void SetTextPadding(RECT rc);					// ���� ���� padding
		bool IsShowHtml();								// �Ƿ�չʾ html
		void SetShowHtml(bool bShowHtml = true);		// ���� �� html

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);								// ִ���¼�
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);		// ���� ����

		void PaintText(HDC hDC);									// ��������

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
		void		SetTextColor1(DWORD _TextColor1);				// ����������ɫ
		DWORD		GetTextColor1();								// ��ȡ������ɫ
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
		LPWSTR  m_pWideText;				// ������ֽڸ�ʽ
		DWORD	m_dwTextColor;				// ������ɫ
		DWORD	m_dwDisabledTextColor;		// ʧЧ״̬������ɫ
		int		m_iFont;					// ���� id
		UINT	m_uTextStyle;				// ���� ��ʽ
		RECT	m_rcTextPadding;			// ���� ���
		bool	m_bShowHtml;				// �Ƿ�չʾ html
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