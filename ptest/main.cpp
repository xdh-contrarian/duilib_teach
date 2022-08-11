/*
* 动态列表demo，
*/

#include "..\DuiLib\UIlib.h"
#include "ptest.h"
using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//加载资源包，可以解压之后查看里面的xml，png等等。

	PTEST* test = new PTEST();
	if (test == NULL) return 0;
	test->Create(NULL, _T("Ptest"), WS_POPUP, WS_EX_STATICEDGE | WS_EX_APPWINDOW | WS_EX_ACCEPTFILES);
	//创建窗口，包括各种窗口属性，和扩展属性

	::ShowWindow(*test, SW_SHOW);//显示窗口

	CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

	return 0;
}
