#include "Windows.h"
#include "iostream"
#include <string>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "EROARE! Utilizare: injector.exe <pid> <dll_path>\n";
		return 1;
	}
	DWORD pid = (DWORD)atoi(argv[1]);

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	const char* path = argv[2];

	char absolutePath[MAX_PATH];
	if (GetFullPathNameA(path, MAX_PATH, absolutePath, NULL) == 0) {
		std::cerr << "Eroare la rezolvarea caii absolute catre dll. ERR " << GetLastError() << "\n";
		return 1;
	}

	size_t pathLength = strlen(absolutePath) + 1;

	if (handle == NULL) {
		std::cerr << "Eroare la OpenProcess(). ERR " << GetLastError() << "\n";
		return 2;
	}

	LPVOID pathAddr = VirtualAllocEx(handle, NULL, pathLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (pathAddr == NULL) {
		std::cerr << "Eroare la VirtualAllocEx(). ERR " << GetLastError() << "\n";
		CloseHandle(handle);
		return 3;
	}

	if (WriteProcessMemory(handle, pathAddr, absolutePath, pathLength, NULL) == 0) {
		std::cerr << "Eroare la WriteProcessMemory(). ERR " << GetLastError() << "\n";
		VirtualFreeEx(handle, pathAddr, 0, MEM_RELEASE);
		CloseHandle(handle);
		return 4;
	}

	FARPROC funcAddr = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	if (funcAddr == NULL) {
		std::cerr << "Eroare la gasirea adresei LoadLibraryA. ERR " << GetLastError() << "\n";
		VirtualFreeEx(handle, pathAddr, 0, MEM_RELEASE);
		CloseHandle(handle);
		return 5;
	}

	HANDLE threadHandle = CreateRemoteThread(handle, NULL, 0, (LPTHREAD_START_ROUTINE)funcAddr, pathAddr, 0, NULL);
	if (threadHandle == NULL) {
		std::cerr << "Eroare la CreateRemoteThread(). ERR " << GetLastError() << "\n";
		VirtualFreeEx(handle, pathAddr, 0, MEM_RELEASE);
		CloseHandle(handle);
		return 6;
	}

	WaitForSingleObject(threadHandle, INFINITE);

	CloseHandle(threadHandle);
	CloseHandle(handle);

	return 0;
}