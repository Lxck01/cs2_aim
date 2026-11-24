// Last updated: 25/11/2026
#pragma once
#include <cstdint>

namespace off {
    // --- module offsets (client.dll) — from cs2-dumper ---
    constexpr uintptr_t dwLocalPlayerPawn = 0x255EAB8;
    constexpr uintptr_t dwViewAngles = 0x2574BE8;
    constexpr uintptr_t dwEntityList = 0x27145B0;

    // --- pawn fields (on C_CSPlayerPawn) ---
    constexpr uintptr_t m_pGameSceneNode = 0x330;
    constexpr uintptr_t m_iHealth = 0x34C;
    constexpr uintptr_t m_iTeamNum = 0x3E7;
    constexpr uintptr_t m_hController = 0x14BC;
    constexpr uintptr_t m_entitySpottedState = 0x1EB8;

    // --- CGameSceneNode ---
    constexpr uintptr_t m_vecAbsOrigin = 0xC8;
    constexpr uintptr_t m_modelState = 0x140;

    // --- CModelState (bone array inside) ---
    constexpr uintptr_t m_pBones = 0x80;
    constexpr uintptr_t boneStride = 0x20;

    // --- visibility (inside m_entitySpottedState) ---
    // +0x0C = m_bSpottedByMask[0] (players 0-31)
    // +0x10 = m_bSpottedByMask[1] (players 32-63) — read via spottedMask + 4
    constexpr uintptr_t spottedMask = 0x0C;

    // --- entity list structure ---
    constexpr uintptr_t entityChunk = 0x10;
    constexpr uintptr_t entityStride = 0x70;

    // --- constants ---
    constexpr int   MAX_SLOTS = 512;
    constexpr float EYE_HEIGHT = 64.f;
}
