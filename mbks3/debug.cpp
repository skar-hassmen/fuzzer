#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <string>

#include "config.hpp"
#include "debug.hpp"


void GetRegisterStates(DEBUG_EVENT DebugEvent, const char* error, HANDLE hProcess) {
	unsigned char buffer[4048] = { 0 };
	SIZE_T recvSize = 0;

	HANDLE thread;
	CONTEXT cont;

	thread = OpenThread(THREAD_ALL_ACCESS, FALSE, DebugEvent.dwThreadId);
	if (thread == NULL)
	{
		std::cout << "OpenThread failed: " << GetLastError() << std::endl;
		return;
	}

	cont.ContextFlags = CONTEXT_FULL;

	if (GetThreadContext(thread, &cont) == false)
	{
		std::cout << "GetThreadContext failed: " << GetLastError() << std::endl;
		CloseHandle(thread);
		return;
	}

	FILE* RegFile = fopen((pathDir + "\\" + "RegisterStates.txt").c_str(), "w");

	fprintf(RegFile, "Error: %s\n", error);
	fprintf(RegFile, "eax : 0x%p\n", cont.Eax);
	fprintf(RegFile, "ebx : 0x%p\n", cont.Ebx);
	fprintf(RegFile, "ecx : 0x%p\n", cont.Ecx);
	fprintf(RegFile, "edx : 0x%p\n", cont.Edx);
	fprintf(RegFile, "eip : 0x%p\n", cont.Eip);
	fprintf(RegFile, "esp : 0x%p\n", cont.Esp);
	fprintf(RegFile, "ebp : 0x%p\n", cont.Ebp);
	fprintf(RegFile, "edi : 0x%p\n", cont.Edi);
	fprintf(RegFile, "esi : 0x%p\n", cont.Esi);
	fprintf(RegFile, "flg : 0x%p\n", cont.EFlags);

	ReadProcessMemory(hProcess, (void*)cont.Esp, buffer, sizeof(buffer), &recvSize);
	if (recvSize != 0)
	{
		fprintf(RegFile, "\nStack (%d bytes read):\n", recvSize);
		for (int i = 0; i < recvSize; i++)
		{
			if ((i + 1) % 4 == 1)
			{
				fprintf(RegFile, "0x%p : ", (void*)((char*)cont.Esp + i));
			}
			if (buffer[i] < 0x10)
			{
				fprintf(RegFile, "0");
			}
			fprintf(RegFile, "%X ", (int)buffer[i]);
			if ((i + 1) % 4 == 0)
			{
				fprintf(RegFile, "\n");
			}
		}
	}
	fprintf(RegFile, "\n");
	fclose(RegFile);
}




bool DebugMode(void) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));

	si.cb = sizeof(si);
	if (CreateProcessA((pathDir + "\\" + exeName).c_str(), NULL, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, pathDir.c_str(), &si, &pi) == false) {
		std::cout << "CreateProcess failed: " << GetLastError() << std::endl;
		return false;
	}
	DEBUG_EVENT DebugEvent;

	while (1) {
		if (WaitForDebugEvent(&DebugEvent, 500) == 0) {
			if (GetLastError() != ERROR_SEM_TIMEOUT) {
				std::cout << "WAIT FOR DEBUG EVENT ERROR : " << GetLastError() << std::endl;
			}
			break;
		}
		if (DebugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT) {
			ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, DBG_CONTINUE);
			continue;
		}
		switch (DebugEvent.u.Exception.ExceptionRecord.ExceptionCode) {
			case EXCEPTION_ACCESS_VIOLATION:
			{
				std::cout << "Access Violation" << std::endl;
				GetRegisterStates(DebugEvent, "Access Violation", pi.hProcess);
				return true;
			}
			case EXCEPTION_STACK_OVERFLOW:
			{
				std::cout << "Stack overflow" << std::endl;
				GetRegisterStates(DebugEvent, "Stack overflow", pi.hProcess);
				return true;
			}
			default:
			{
				ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, DBG_CONTINUE);
				break;
			}
		}
	}
	return false;
}
