// Last updated: 14/11/2026

#pragma once
#include <cstdint>

#define CS2_AIM_VERSION "v1.0.0"

namespace off {
    // --- module offsets (client.dll) — from cs2-dumper ---
    constexpr uintptr_t dwEntityList = 0x2709010;
    constexpr uintptr_t dwLocalPlayerPawn = 0x2553D38;
    constexpr uintptr_t dwViewAngles = 0x256A4B8;

    // --- scene node / pawn fields ---
    constexpr uintptr_t m_pGameSceneNode = 0x330;
    constexpr uintptr_t m_iHealth = 0x34C;
    constexpr uintptr_t m_iTeamNum = 0x3E7;
    constexpr uintptr_t m_vecAbsOrigin = 0xC8;

    // --- bones ---
    constexpr uintptr_t m_modelState = 0x140;
    constexpr uintptr_t m_pBones = 0x80;

    // --- visibility check ---
    // m_bSpotted lives inside C_CSPlayerPawn::m_entitySpottedState.
    // VERIFY against cs2-dumper output before enabling vis_check
    // in aim.cfg. If this offset is wrong, vis_check will filter
    // targets randomly (some invisible some not).
    // Look in dumper for: C_CSPlayerPawn -> m_entitySpottedState
    //                     then m_bSpotted inside it (usually 0x08).
    constexpr uintptr_t m_bSpotted = 0x1E70;

    // --- structural constants (do NOT edit unless you re-verified them) ---
    constexpr uintptr_t entityChunk = 0x10;
    constexpr uintptr_t entityStride = 0x70;
    constexpr uintptr_t boneStride = 0x20;

    constexpr int   MAX_SLOTS = 512;
    constexpr float EYE_HEIGHT = 64.f;
}
