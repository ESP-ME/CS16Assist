#include "stdafx.h"
#include "UIThread.h"
#include "Spirit.h"

#pragma comment(lib, "comctl32.lib")

UIControlVal controlVal;
Spirit spirit;

DWORD WINAPI ThreadShow(LPVOID lpPatameter) {
	char szPath[MAX_PATH] = { 0 };
	char szBuf[1024] = { 0 };
	GetModuleFileName(NULL, szPath, MAX_PATH);
	DialogBox((HINSTANCE)lpPatameter, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)MainDialogProc);
	//DWORD opRes = GetLastError();
	//sprintf(szBuf, "DLL�Ѿ�ע�뵽���� %s [Pid = %d], ����Box���أ�%d \n", szPath, GetCurrentProcessId(), opRes);
	//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
	return 0;
}

LRESULT CALLBACK MainDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent, ret;
	char szBuf[1024] = { 0 };
	HWND checkHnd;

	switch (message) {
	case WM_INITDIALOG:
		checkHnd = GetDlgItem(hWnd, IDC_CHECK3);
		EnableWindow(checkHnd, FALSE);
		checkHnd = GetDlgItem(hWnd, IDC_CHECK4);
		EnableWindow(checkHnd, FALSE);
		return TRUE;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDC_CHECK1:
			checkHnd = GetDlgItem(hWnd, IDC_CHECK1);
			ret = SendMessage(checkHnd, BM_GETCHECK, 0, 0);
			if (BST_CHECKED == ret) {
				//sprintf(szBuf, "ѡ�������ӵ�check box");
				//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				controlVal.setIsCheckInfiniteBullet(TRUE);
			}
			else {
				//sprintf(szBuf, "ȡ��ѡ�������ӵ�check box");
				//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				controlVal.setIsCheckInfiniteBullet(FALSE);
			}
			return TRUE;
		case IDC_CHECK2:
			checkHnd = GetDlgItem(hWnd, IDC_CHECK2);
			ret = SendMessage(checkHnd, BM_GETCHECK, 0, 0);
			if (BST_CHECKED == ret) {
				//sprintf(szBuf, "ѡ����������check box");
				//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				controlVal.setIsCheckInfiniteLife(TRUE);
			}
			else {
				controlVal.setIsCheckInfiniteLife(FALSE);
			}
			return TRUE;
		case IDC_CHECK3:
			checkHnd = GetDlgItem(hWnd, IDC_CHECK3);
			ret = SendMessage(checkHnd, BM_GETCHECK, 0, 0);
			if (BST_CHECKED == ret) {
				//sprintf(szBuf, "ѡ���ƶ�����check box");
				//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				controlVal.setIsCheckAcce(TRUE);
			}
			else {
				controlVal.setIsCheckAcce(FALSE);
			}
			return TRUE;
		case IDC_CHECK4:
			sprintf(szBuf, "������...");
			MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		/**
		 * ж��DLL TODO
		 */
		EndDialog(hWnd, 0);
		break;
	}
	return 0;
}