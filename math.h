#pragma once
#include <cmath>

struct Vec3 { float x, y, z; };

constexpr float D2R = 3.14159265f / 180.f;
constexpr float R2D = 180.f / 3.14159265f;

inline float NormDeg(float a) {
    while (a > 180.f) a -= 360.f;
    while (a < -180.f) a += 360.f;
    return a;
}
inline Vec3 CalcAngle(const Vec3& s, const Vec3& d) {
    float dx = d.x - s.x, dy = d.y - s.y, dz = d.z - s.z;
    float hyp = sqrtf(dx * dx + dy * dy);
    return { atan2f(-dz, hyp) * R2D, atan2f(dy, dx) * R2D, 0.f };
}
inline Vec3 Forward(const Vec3& a) {
    float p = a.x * D2R, y = a.y * D2R;
    return { cosf(p) * cosf(y), cosf(p) * sinf(y), -sinf(p) };
}
inline float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vec3 Normalize(const Vec3& v) {
    float l = sqrtf(Dot(v, v));
    return l < 1e-4f ? Vec3{ 1,0,0 } : Vec3{ v.x / l, v.y / l, v.z / l };
}
inline float FovBetween(const Vec3& a, const Vec3& b) {
    float d = Dot(a, b);
    if (d > 1.f) d = 1.f;
    if (d < -1.f) d = -1.f;
    return acosf(d) * R2D;
}
