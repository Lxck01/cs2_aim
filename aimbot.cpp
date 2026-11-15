#include "aimbot.h"
#include "memory.h"
#include "offsets.h"
#include <cmath>

// Personal visibility: true only if the local player's slot bit is set
// in the enemy's m_bSpottedByMask. Team-wide m_bSpotted is intentionally
// not used — it fires when any teammate sees the enemy, which is what
// caused locks through walls.
static bool IsVisible(uintptr_t ent, int myIndex) {
    if (myIndex < 0 || myIndex >= 64) return false;

    uintptr_t spottedBase = ent + off::m_entitySpottedState;
    int word = myIndex / 32;   // 0 or 1
    int bit = myIndex % 32;   // 0..31

    uint32_t mask = Rd<uint32_t>(spottedBase + off::spottedMask + word * 4);
    return (mask & (1u << bit)) != 0;
}

Target FindTarget(const Config& cfg, const Vec3& viewAngles) {
    Target result{ false,{} };

    uintptr_t local = Rd<uintptr_t>(g_client + off::dwLocalPlayerPawn);
    if (!Valid(local)) return result;
    if (Rd<int>(local + off::m_iHealth) <= 0) return result;
    int myTeam = Rd<int>(local + off::m_iTeamNum);

    uintptr_t myNode = Rd<uintptr_t>(local + off::m_pGameSceneNode);
    if (!Valid(myNode)) return result;

    Vec3 eye = Rd<Vec3>(myNode + off::m_vecAbsOrigin);
    eye.z += off::EYE_HEIGHT;

    Vec3 fwd = Forward(viewAngles);

    uintptr_t list = Rd<uintptr_t>(g_client + off::dwEntityList);
    uintptr_t chunk = Valid(list) ? Rd<uintptr_t>(list + off::entityChunk) : 0;
    if (!Valid(chunk)) return result;

    // Resolve local player's entity-list index once per tick.
    // Only needed for vis_check, so skip the scan entirely otherwise.
    int myIndex = -1;
    if (cfg.visCheck) {
        // Controller index - 1 == player slot, which is what the mask is indexed by
        uint32_t hCtrl = Rd<uint32_t>(local + off::m_hController);
        if (hCtrl == 0xFFFFFFFF) return result;
        myIndex = static_cast<int>(hCtrl & 0x7FFF) - 1;
        if (myIndex < 0 || myIndex >= 64) return result;
    }

    float bestFov = cfg.fovDeg;
    Vec3  bestAng{};

    for (int i = 1; i < off::MAX_SLOTS; ++i) {
        uintptr_t ent = Rd<uintptr_t>(chunk + off::entityStride * i);
        if (!Valid(ent) || ent == local) continue;

        if (Rd<int>(ent + off::m_iHealth) <= 0) continue;
        if (cfg.teamCheck && Rd<int>(ent + off::m_iTeamNum) == myTeam) continue;
        if (cfg.visCheck && !IsVisible(ent, myIndex)) continue;

        uintptr_t node = Rd<uintptr_t>(ent + off::m_pGameSceneNode);
        if (!Valid(node)) continue;

        Vec3 org = Rd<Vec3>(node + off::m_vecAbsOrigin);
        uintptr_t bones = Rd<uintptr_t>(node + off::m_modelState + off::m_pBones);
        if (!Valid(bones)) continue;

        Vec3 head = Rd<Vec3>(bones + cfg.headBone * off::boneStride);
        if (head.x == 0 && head.y == 0 && head.z == 0) continue;
        if (fabsf(head.x - org.x) > 100.f) continue;
        if (fabsf(head.y - org.y) > 100.f) continue;
        if (fabsf(head.z - org.z) > 100.f) continue;

        float f = FovBetween(fwd, Normalize({ head.x - eye.x, head.y - eye.y, head.z - eye.z }));
        if (f >= bestFov) continue;

        bestFov = f;
        bestAng = CalcAngle(eye, head);
        result.found = true;
        result.angle = bestAng;
    }

    return result;
}
