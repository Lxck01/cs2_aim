#pragma once
#include "math.h"
#include "config.h"

struct Target {
    bool found;
    Vec3 angle;
};

Target FindTarget(const Config& cfg, const Vec3& viewAngles);
