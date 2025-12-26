#pragma once 

class PerlinNoise {
public:
	explicit PerlinNoise(unsigned int seed = 0);

	float sample(float x, float y) const;

	float fbm(float x, float y,
		int octaves = 8,
		float lacunarity = 2.f,
		float persistence = 0.6f) const;

private:
	unsigned int m_seed;
};