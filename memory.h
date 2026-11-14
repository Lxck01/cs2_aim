#pragma once
#define NOMINMAX
#include <windows.h>
#include <cstdint>
#include <cstddef>

extern HANDLE    g_proc;
extern uintptr_t g_client;
extern DWORD     g_pid;

template <typename T> inline T Rd(uintptr_t a) {
    T v{};
    if (a) ReadProcessMemory(g_proc, (LPCVOID)a, &v, sizeof(T), nullptr);
    return v;
}
inline bool Wr(uintptr_t a, const void* d, size_t n) {
    return WriteProcessMemory(g_proc, (LPVOID)a, d, n, nullptr) != 0;
}
inline bool Valid(uintptr_t a) { return a > 0x10000 && a < 0x7FFFFFFFFFFF; }

bool Attach();
bool GameFocused();
