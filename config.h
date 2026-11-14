#pragma once

struct Config {
    int   aimKey;
    int   exitKey;
    float fovDeg;
    float smooth;
    float maxDegTick;
    int   headBone;
    int   tickMs;
    bool  teamCheck;
    bool  visCheck;
};

extern Config g_cfg;

void LoadCfg();
int  ParseVK(const char* s);
