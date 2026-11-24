#include "config.h"
#define NOMINMAX
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

Config g_cfg = {
    VK_XBUTTON2,   // aimKey
    VK_END,        // exitKey
    2.0f,          // fovDeg
    5.0f,          // smooth
    2.0f,          // maxDegTick
    7,             // aimBone
    4,             // tickMs
    true,          // teamCheck
    false          // visCheck
};

int ParseVK(const char* s) {
    if (!_stricmp(s, "MOUSE4") || !_stricmp(s, "XBUTTON1")) return VK_XBUTTON1;
    if (!_stricmp(s, "MOUSE5") || !_stricmp(s, "XBUTTON2")) return VK_XBUTTON2;
    if (!_stricmp(s, "LEFT") || !_stricmp(s, "LBUTTON"))  return VK_LBUTTON;
    if (!_stricmp(s, "RIGHT") || !_stricmp(s, "RBUTTON"))  return VK_RBUTTON;
    if (!_stricmp(s, "MIDDLE") || !_stricmp(s, "MBUTTON"))  return VK_MBUTTON;
    if (!_stricmp(s, "SHIFT"))  return VK_SHIFT;
    if (!_stricmp(s, "CTRL"))   return VK_CONTROL;
    if (!_stricmp(s, "ALT"))    return VK_MENU;
    if (!_stricmp(s, "SPACE"))  return VK_SPACE;
    if (!_stricmp(s, "INSERT") || !_stricmp(s, "INS")) return VK_INSERT;
    if (!_stricmp(s, "DELETE") || !_stricmp(s, "DEL")) return VK_DELETE;
    if (!_stricmp(s, "HOME"))   return VK_HOME;
    if (!_stricmp(s, "END"))    return VK_END;
    if (!_stricmp(s, "PGUP"))   return VK_PRIOR;
    if (!_stricmp(s, "PGDN"))   return VK_NEXT;
    if (s[0] == 'F' || s[0] == 'f') {
        int n = atoi(s + 1);
        if (n >= 1 && n <= 12) return VK_F1 + n - 1;
    }
    if (strlen(s) == 1) {
        char c = (char)toupper((unsigned char)s[0]);
        if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) return c;
    }
    int v = atoi(s);
    return (v > 0 && v < 256) ? v : 0;
}

static bool ParseBool(const char* s) {
    return !_stricmp(s, "true") || !_stricmp(s, "1") || !_stricmp(s, "yes") || !_stricmp(s, "on");
}

void LoadCfg() {
    FILE* f = nullptr;
    if (fopen_s(&f, "aim.cfg", "r") != 0 || !f) {
        printf("[cfg] aim.cfg not found, using defaults\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char* p = line;
        char* hash = strchr(p, '#'); if (hash) *hash = 0;
        char* semi = strchr(p, ';'); if (semi) *semi = 0;

        char* eq = strchr(p, '=');
        if (!eq) continue;
        *eq = 0;

        char* key = p;
        while (*key == ' ' || *key == '\t') ++key;
        char* ke = key + strlen(key);
        while (ke > key && strchr(" \t\r\n", ke[-1])) --ke;
        *ke = 0;

        char* val = eq + 1;
        while (*val == ' ' || *val == '\t') ++val;
        char* ve = val + strlen(val);
        while (ve > val && strchr(" \t\r\n", ve[-1])) --ve;
        *ve = 0;

        if (!_stricmp(key, "aim_key")) { int vk = ParseVK(val); if (vk) g_cfg.aimKey = vk; }
        else if (!_stricmp(key, "exit_key")) { int vk = ParseVK(val); if (vk) g_cfg.exitKey = vk; }
        else if (!_stricmp(key, "fov")) { float v = (float)atof(val); if (v > 0.1f && v < 90.f)  g_cfg.fovDeg = v; }
        else if (!_stricmp(key, "smooth")) { float v = (float)atof(val); if (v >= 1.f && v <= 100.f) g_cfg.smooth = v; }
        else if (!_stricmp(key, "max_deg_tick")) { float v = (float)atof(val); if (v > 0.05f && v < 90.f) g_cfg.maxDegTick = v; }
        else if (!_stricmp(key, "aim_bone")) { int v = atoi(val); if (v >= 0 && v < 256) g_cfg.aimBone = v; }
        else if (!_stricmp(key, "tick_ms")) { int v = atoi(val); if (v >= 1 && v <= 50)  g_cfg.tickMs = v; }
        else if (!_stricmp(key, "team_check")) { g_cfg.teamCheck = ParseBool(val); }
        else if (!_stricmp(key, "vis_check")) { g_cfg.visCheck = ParseBool(val); }
    }
    fclose(f);
    printf("[cfg] loaded aim.cfg\n");
}
