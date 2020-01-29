#pragma once

#include<stdio.h>

DWORD ProcessToPid(char *processName);

BOOL WINAPI InjectDllToProcess(DWORD dwTargetPid, LPCTSTR dllPath);