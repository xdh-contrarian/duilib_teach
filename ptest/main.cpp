/*
* ��̬�б�demo��
*/

#include "..\DuiLib\UIlib.h"
#include "ptest.h"
using namespace DuiLib;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("ListRes.zip"));//������Դ�������Խ�ѹ֮��鿴�����xml��png�ȵȡ�

	PTEST* test1 = new PTEST();
	if (test1 == NULL) return 0;
	test1->Create(NULL, _T("Ptest"), NULL, NULL);
	//�������ڣ��������ִ������ԣ�����չ����
	// 
	// �㲥��Ϣ
	//static UINT showMyappMsg = RegisterWindowMessage(L"MYAPP_SHOW");
	//DWORD dwRecipients = BSM_APPLICATIONS;
	//BroadcastSystemMessage(BSF_POSTMESSAGE, &dwRecipients, showMyappMsg, NULL,NULL);

	// PostMessageA
	//static UINT showMyappMsg = RegisterWindowMessage(L"MYAPP_SHOW");
	//PostMessageA(HWND_BROADCAST, showMyappMsg,0,0);
	//::ShowWindow(*test1, SW_SHOW);//��ʾ����
	test1->ShowWindow(true);


	CPaintManagerUI::MessageLoop();//����duilib����Ϣѭ����ͨ��������Windows�ǻ�����Ϣ���ƵĲ���ϵͳ

	return 0;
}
