#include "include/PerlinNoise.hpp"
#include <cmath>

static unsigned int hash(int x, int y, unsigned int seed) {
	unsigned int h = seed;
    h ^= x * 374761393u;
    h ^= y * 668265263u;
    h = (h ^ (h >> 13)) * 1274126177u;
    return h;
}

static void gradient(int x, int y, unsigned int seed, float& gx, float& gy) {
    unsigned int h = hash(x, y, seed);
    float angle = (h % 360) * 3.14159265f / 180.f;
    gx = std::cos(angle);
    gy = std::sin(angle);
}

static float fade(float t) {
    return t * t * t * (t * (6.f * t - 15.f) + 10.f);
}

static float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

PerlinNoise::PerlinNoise(unsigned int seed) : m_seed(seed) {}

float PerlinNoise::sample(float x, float y) const {
    int x0 = static_cast<int>(std::floor(x));
    int y0 = static_cast<int>(std::floor(y));

    float xf = x - x0;
    float yf = y - y0;

    float gx00, gy00, gx01, gy01, gx10, gy10, gx11, gy11;
    gradient(x0, y0, m_seed, gx00, gy00);
    gradient(x0, y0 + 1, m_seed, gx01, gy01);
    gradient(x0 + 1, y0, m_seed, gx10, gy10);
    gradient(x0 + 1, y0 + 1, m_seed, gx11, gy11);

    float dx00 = xf;
    float dy00 = yf;

    float dx01 = xf;
    float dy01 = yf - 1.f;

    float dx10 = xf - 1.f;
    float dy10 = yf;

    float dx11 = xf - 1.f;
    float dy11 = yf - 1.f;

    float n00 = gx00 * dx00 + gy00 * dy00;
    float n01 = gx01 * dx01 + gy01 * dy01;
    float n10 = gx10 * dx10 + gy10 * dy10;
    float n11 = gx11 * dx11 + gy11 * dy11;

    float u = fade(xf);
    float v = fade(yf);

    float nx0 = lerp(n00, n10, u);
    float nx1 = lerp(n01, n11, u);

    return lerp(nx0, nx1, v);
}