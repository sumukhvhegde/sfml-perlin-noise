#pragma once 

class PerlinNoise {
public:
	explicit PerlinNoise(unsigned int seed = 0);

	float sample(float x, float y) const;

private:
	unsigned int m_seed;
};