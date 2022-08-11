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
    };

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

    UINT GetClassStyle() const
    {
        return CS_DBLCLKS;
    };

private:

};
