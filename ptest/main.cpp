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

	PTEST* test1 = new PTEST();
	if (test1 == NULL) return 0;
	test1->Create(NULL, _T("Ptest"), NULL, NULL);
	//创建窗口，包括各种窗口属性，和扩展属性
	// 
	// 广播消息
	//static UINT showMyappMsg = RegisterWindowMessage(L"MYAPP_SHOW");
	//DWORD dwRecipients = BSM_APPLICATIONS;
	//BroadcastSystemMessage(BSF_POSTMESSAGE, &dwRecipients, showMyappMsg, NULL,NULL);

	// PostMessageA
	//static UINT showMyappMsg = RegisterWindowMessage(L"MYAPP_SHOW");
	//PostMessageA(HWND_BROADCAST, showMyappMsg,0,0);
	//::ShowWindow(*test1, SW_SHOW);//显示窗口
	test1->ShowWindow(true);


	CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

	return 0;
}
