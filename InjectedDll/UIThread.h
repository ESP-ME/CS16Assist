#pragma once
#include <windows.h>
#include<stdio.h>
#include <commctrl.h>//�߼��ؼ�������
#include <commdlg.h>
#include "resource.h"
#include "UIControlVal.H"

extern UIControlVal controlVal;

DWORD WINAPI ThreadShow(LPVOID lpPatameter);

LRESULT CALLBACK MainDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
