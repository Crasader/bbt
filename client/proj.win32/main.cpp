#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "stdafx.h"
#include <stdlib.h>
#include <crtdbg.h>

USING_NS_CC;

#define USE_WIN32_CONSOLE

//��main�����еõ���������תΪgetopt_long��Ҫ��charָ�����顣ͬʱҲ�����ʣ�Ϊʲô__argv�ò��������в���
inline void AllocCharArrayFromWideChar(LPTSTR srcLpChar, char** dest)
{
	char* srcChar = AllocUTF8FromWideChar(srcLpChar, wcslen(srcLpChar));

	//��ΪlpCmdLine�ǹ��˵�·���ģ���������Ҫ����
	dest[0] = "";

	int index = 1;
	const char* space = " ";
	dest[index] = strtok(srcChar, space);
	while(dest[index])
	{
		dest[++index] = strtok(NULL, space);
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE 
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
	auto* eglView = Director::getInstance()->getOpenGLView();//CCEGLView::sharedOpenGLView();
	if(!eglView) {
		eglView = GLViewImpl::create("bbt");
		Director::getInstance()->setOpenGLView(eglView);
	}
	int			 nRetCode		= 0;

	float       fWidth = 640;
	float       fHeight = 360;
	option LongOpt[] =
	{
		{"width", no_argument, NULL, 'w'},
		{"height", required_argument, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	char **p = new char *[__argc];
	AllocCharArrayFromWideChar(lpCmdLine, p);

	while (true)
	{
		int nOpt = getopt_long(__argc, p, "w:h:c:a:", LongOpt, NULL);
		if (nOpt == -1)
			break;

		switch (nOpt)
		{
		case 'w':
			fWidth = atoi(optarg);
			break;

		case 'h':
			fHeight = atoi(optarg);
			break;

		default:
			printf("client.exe -w 640 -h 360");
			break;
		}
	}

	eglView->setFrameSize(fWidth, fHeight);
    return Application::getInstance()->run();
}
