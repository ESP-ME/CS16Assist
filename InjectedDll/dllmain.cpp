// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "stdafx.h"
#include "UIThread.h"
#include "HookThread.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
		case DLL_PROCESS_ATTACH:
			//启动控制界面
			CreateThread(NULL, 0, ThreadShow, hModule, 0, NULL);
			//启动子弹数量,生命值和移动速度控制线程
			CreateThread(NULL, 0, HookThreadFunc, hModule, 0, NULL);
			break;
    }
    return TRUE;
}

