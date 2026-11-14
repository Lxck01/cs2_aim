#include "memory.h"
#include <tlhelp32.h>

HANDLE    g_proc = nullptr;
uintptr_t g_client = 0;
DWORD     g_pid = 0;

bool Attach() {
    HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (s == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe{ sizeof(pe) };
    for (BOOL ok = Process32FirstW(s, &pe); ok; ok = Process32NextW(s, &pe))
        if (!lstrcmpiW(pe.szExeFile, L"cs2.exe")) { g_pid = pe.th32ProcessID; break; }
    CloseHandle(s);
    if (!g_pid) return false;

    g_proc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, g_pid);
    if (!g_proc) return false;

    HANDLE m = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, g_pid);
    MODULEENTRY32W me{ sizeof(me) };
    for (BOOL ok = Module32FirstW(m, &me); ok; ok = Module32NextW(m, &me))
        if (!lstrcmpiW(me.szModule, L"client.dll")) { g_client = (uintptr_t)me.modBaseAddr; break; }
    CloseHandle(m);
    return g_client != 0;
}

bool GameFocused() {
    HWND h = GetForegroundWindow();
    DWORD p = 0; if (h) GetWindowThreadProcessId(h, &p);
    return p == g_pid;
}
