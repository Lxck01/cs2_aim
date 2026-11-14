#include <windows.h>
#include <cstdio>
#include <cmath>
#include "config.h"
#include "memory.h"
#include "math.h"
#include "aimbot.h"
#include "offsets.h"

int main() {
    SetConsoleTitleA("cs2_aim");
    printf("=== %s ===\n", CS2_AIM_VERSION);
    LoadCfg();
    printf("[cfg] aim=%d exit=%d fov=%.2f smooth=%.2f maxTick=%.2f bone=%d tick=%dms team=%d vis=%d\n",
        g_cfg.aimKey, g_cfg.exitKey, g_cfg.fovDeg, g_cfg.smooth,
        g_cfg.maxDegTick, g_cfg.headBone, g_cfg.tickMs,
        (int)g_cfg.teamCheck, (int)g_cfg.visCheck);

    printf("[*] waiting for cs2.exe...\n");
    while (!Attach()) Sleep(1000);
    printf("[+] attached @ %p\n", (void*)g_client);
    printf("[+] hold aim key, exit key quits\n");

    const uintptr_t va = g_client + off::dwViewAngles;

    while (true) {
        if (GetAsyncKeyState(g_cfg.exitKey) & 0x8000) break;
        if (!(GetAsyncKeyState(g_cfg.aimKey) & 0x8000) || !GameFocused()) {
            Sleep(g_cfg.tickMs); continue;
        }

        Vec3 view = Rd<Vec3>(va);
        if (!(fabsf(view.x) <= 90.f && fabsf(view.y) <= 180.f)) {
            Sleep(g_cfg.tickMs); continue;
        }

        Target t = FindTarget(g_cfg, view);
        if (!t.found) { Sleep(g_cfg.tickMs); continue; }

        Vec3 cur = Rd<Vec3>(va);
        float dY = NormDeg(t.angle.y - cur.y);
        float dP = NormDeg(t.angle.x - cur.x);
        if (fabsf(dY) < 0.05f && fabsf(dP) < 0.05f) { Sleep(g_cfg.tickMs); continue; }

        float sy = dY / g_cfg.smooth, sp = dP / g_cfg.smooth;
        if (sy > g_cfg.maxDegTick) sy = g_cfg.maxDegTick;
        if (sy < -g_cfg.maxDegTick) sy = -g_cfg.maxDegTick;
        if (sp > g_cfg.maxDegTick) sp = g_cfg.maxDegTick;
        if (sp < -g_cfg.maxDegTick) sp = -g_cfg.maxDegTick;

        Vec3 next{ cur.x + sp, NormDeg(cur.y + sy), 0.f };
        Wr(va, &next, sizeof(next));

        Sleep(g_cfg.tickMs);
    }

    if (g_proc) CloseHandle(g_proc);
    printf("[+] bye\n");
    system("pause");
    return 0;
}
