#pragma once

#include "resource.h"

#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>

#include "..\DuiLib\UIlib.h"
using namespace DuiLib;


class PTEST : public WindowImplBase
{
public:
    PTEST() {
        m_bBkColor = false;
    };
	~PTEST() {};

    CDuiString GetSkinFolder()
    {
        return _T("skin\\Ptest\\");
    }

    CDuiString GetSkinFile()
    {
        return _T("ptest.xml");
    }

    LPCTSTR GetWindowClassName() const
    {
        return _T("Ptest");
    };
    void OnClick(TNotifyUI& msg);
    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT	OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
    CVerticalLayoutUI* bk;
    bool               m_bBkColor;
};
