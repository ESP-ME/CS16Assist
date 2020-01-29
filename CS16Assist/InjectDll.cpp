#include "stdafx.h"
#include "InjectDll.h"
#include <windows.h>
#include <TlHelp32.h>

typedef LONG NTSTATUS;

#define STATUS_SUCCESS                      ((NTSTATUS) 0x00000000L)
#define STATUS_UNSUCCESSFUL					((NTSTATUS) 0xC0000001L)
#define STATUS_INFO_LENGTH_MISMATCH			((NTSTATUS) 0xC0000004L) 
#define STATUS_IO_DEVICE_ERROR              ((NTSTATUS) 0xC0000185L) 

typedef struct _INJECT_DATA {
	BYTE ShellCode[0x30];
	LPVOID lpThreadStartRoutine;
	LPVOID lpParameter;
	LPVOID AddrOfZwTerminateThread;
} INJECT_DATA ;

typedef struct _CLIENT_ID {
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID;
typedef CLIENT_ID *PCLIENT_ID;

typedef PVOID PUSER_THREAD_START_ROUTINE;

typedef NTSTATUS(__stdcall *PCreateThread)(
	IN HANDLE Process,
	IN PSECURITY_DESCRIPTOR ThreadSecurityDescriptor OPTIONAL,
	IN BOOLEAN CreateSuspended,
	IN ULONG ZeroBits OPTIONAL,
	IN SIZE_T MaximumStackSize OPTIONAL,
	IN SIZE_T CommittedStackSize OPTIONAL,
	IN PUSER_THREAD_START_ROUTINE StartAddress,
	IN PVOID Parameter OPTIONAL,
	OUT PHANDLE Thread OPTIONAL,
	OUT PCLIENT_ID ClientId OPTIONAL
	);

HANDLE RtlCreateRemoteThread(
	IN  HANDLE hProcess,
	IN  LPSECURITY_ATTRIBUTES lpThreadAttributes,
	IN  DWORD dwStackSize,
	IN  LPTHREAD_START_ROUTINE lpStartAddress,
	IN  LPVOID lpParameter,
	IN  DWORD dwCreationFlags,
	OUT LPDWORD lpThreadId
); 

PCreateThread RtlCreateUserThread;

DWORD ProcessToPid(char *processName) {
	HANDLE hProcessSnap = NULL;
	DWORD processId = 0;
	PROCESSENTRY32 pe32 = {0};
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//打开进程快照
	if (hProcessSnap == (HANDLE)-1) {
		printf("\n CreateToolhelp32Snapshot() Error: %d", GetLastError());
		return 0;
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32)) {
		do {
			if (!_stricmp(processName, pe32.szExeFile)) {
				processId = pe32.th32ProcessID;
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	} else {
		printf("\n Process32First() Error: %d", GetLastError());
		return 0;
	}
	CloseHandle(hProcessSnap);//关闭系统进程快照的句柄
	return processId;
}

BOOL WINAPI InjectDllToProcess(DWORD dwTargetPid, LPCTSTR dllPath) {

	/**
     * 打开目标进程
     */
	HANDLE hProc = NULL;
	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwTargetPid);
	if (hProc == NULL) {
		printf("[-] OpenProcess Failed. \n");
		return FALSE;
	}

	/**
	 * 在远程进程的内存地址空间分配DLL路径名缓冲区
	 */
	LPTSTR psLibFileRemote = NULL;
	psLibFileRemote = (LPTSTR)VirtualAllocEx(hProc, NULL, lstrlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);   
	if (psLibFileRemote == NULL) {
		printf("[-] VirtualAllocEx Failed.\n");
		return FALSE;
	}

	/**
	 * 在远程进程的内存地址空间写入DLL路径名缓冲区
	 */
	if (WriteProcessMemory(hProc, psLibFileRemote, (void *)dllPath, lstrlen(dllPath) + 1, NULL) == 0) {
		printf("[-] WriteProcessMemory Failed.\n");
		return FALSE;
	}

	/**
	 * 计算LoadLibraryA的入口地址
	 */
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");
	if (pfnStartAddr == NULL) {
		printf("[-] GetProcAddress Failed.\n");
		return FALSE;
	}

	HANDLE hThread = RtlCreateRemoteThread(hProc, NULL, 0, pfnStartAddr, psLibFileRemote, 0, NULL);
	if (hThread == NULL) {
		printf("[-] CreateRemoteThread Failed. ErrCode = %d\n", GetLastError());
		return FALSE;
	}
	printf("[*] Inject Succesfull.\n");
	return TRUE;
}
#ifdef _WIN64
EXTERN_C VOID ShellCodeFun64(VOID);
#else
__declspec (naked)
VOID ShellCodeFun(VOID) {
	__asm {
		call L001
		L001:
		pop ebx
		sub ebx,5
        push dword ptr ds:[ebx]INJECT_DATA.lpParameter //lpParameter
		call dword ptr ds:[ebx]INJECT_DATA.lpThreadStartRoutine //ThreadProc
		xor eax, eax
		push eax
		push -2
		call dword ptr ds:[ebx]INJECT_DATA.AddrOfZwTerminateThread //ZwTerminateThread
		nop  //no return
		nop
		nop
		nop
		nop
	}
}
#endif


VOID PrepareShellCode(BYTE *pOutShellCode) {
#ifdef _WIN64
	BYTE *pShellcodeStart = (BYTE*)ShellCodeFun64;
#else
	BYTE *pShellcodeStart = (BYTE *)ShellCodeFun;
#endif

	/**
	 * 位移量 = 目的地址 - 起始地址 - 跳转指令本身的长度
	 * 转移指令机器码 = 转移类别机器码 + 位移量
	 * 下面是计算jmp长转移的目的地址，0xE9表示jmp
	 */
	BYTE *pShellcodeEnd = 0;
	SIZE_T ShellCodeSize = 0;
	if (pShellcodeStart[0] == 0xE9) {
		pShellcodeStart = pShellcodeStart + *(ULONG*)(pShellcodeStart + 1) + 5;
	}

	pShellcodeEnd = pShellcodeStart;
	while (memcmp(pShellcodeEnd, "\x90\x90\x90\x90\x90", 5) != 0) {
		pShellcodeEnd++;
	}
	ShellCodeSize = pShellcodeEnd - pShellcodeStart;
	printf("[*] Shellcode Len = %d\n", ShellCodeSize);
	memcpy(pOutShellCode, pShellcodeStart, ShellCodeSize);
}

HANDLE RtlCreateRemoteThread(
	IN  HANDLE hProcess,
	IN  LPSECURITY_ATTRIBUTES lpThreadAttributes,
	IN  DWORD dwStackSize,
	IN  LPTHREAD_START_ROUTINE lpStartAddress,
	IN  LPVOID lpParameter,
	IN  DWORD dwCreationFlags,
	OUT LPDWORD lpThreadId
) {
	NTSTATUS status = STATUS_SUCCESS;
	CLIENT_ID cId;
	HANDLE hThread = NULL;
	SIZE_T dwIoCnt = 0;

	if (hProcess == NULL
		|| lpStartAddress == NULL) {
		return NULL;
	}

	/**
	 * 获取Native API函数地址
	 */
	RtlCreateUserThread = (PCreateThread)GetProcAddress(GetModuleHandle("ntdll"), "RtlCreateUserThread");
	if (RtlCreateUserThread == NULL) {
		return NULL;
	}

	/**
	 * 在目标进程中申请内存写入ShellCode
	 */
	PBYTE pMem = (PBYTE)VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (pMem == NULL) {
		return NULL;
	}
	printf("[*] pMem = 0x%p\n", pMem);

	INJECT_DATA data;
	ZeroMemory(&data, sizeof(INJECT_DATA));
	PrepareShellCode(data.ShellCode);
	data.lpParameter = lpParameter;
	data.lpThreadStartRoutine = lpStartAddress;
	data.AddrOfZwTerminateThread = GetProcAddress(GetModuleHandle("ntdll"), "ZwTerminateThread");

	if (!WriteProcessMemory(hProcess, pMem, &data, sizeof(INJECT_DATA), &dwIoCnt)) {
		printf("[-] WriteProcessMemory Failed!\n");
		VirtualFreeEx(hProcess, pMem, 0, MEM_RELEASE);
		return NULL;
	}
	printf("[*] ShellCode Write OK.\n");

	status = RtlCreateUserThread(hProcess, lpThreadAttributes
		, TRUE,
		0,
		dwStackSize,
		0,
		(PUSER_THREAD_START_ROUTINE)pMem,
		NULL,
		&hThread,
		&cId);
	if (status >= 0) {
		printf("[*] 线程创建成功!\n");
		if (lpThreadId != NULL) {
			*lpThreadId = (DWORD)cId.UniqueThread;
		}
		if (!(dwCreationFlags & CREATE_SUSPENDED)) {
			ResumeThread(hThread);
		}
	}
	return hThread;
	
}

