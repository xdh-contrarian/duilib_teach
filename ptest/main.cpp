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

	PTEST* test = new PTEST();
	if (test == NULL) return 0;
	test->Create(NULL, _T("Ptest"), WS_POPUP, WS_EX_STATICEDGE | WS_EX_APPWINDOW | WS_EX_ACCEPTFILES);
	//�������ڣ��������ִ������ԣ�����չ����

	::ShowWindow(*test, SW_SHOW);//��ʾ����

	CPaintManagerUI::MessageLoop();//����duilib����Ϣѭ����ͨ��������Windows�ǻ�����Ϣ���ƵĲ���ϵͳ

	return 0;
}
