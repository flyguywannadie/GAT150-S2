#pragma once
#include <random>

namespace max
{
	inline void seedRandom(unsigned int seed) { srand(seed); }
	inline int random() { return rand(); }
	inline int random(unsigned int max) { return random() % max; } // 0 && 1 less than MAX number
	inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } // between min & max

	inline float randomf() { return random() / (float)RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float max, float min) { return min + (randomf() * (max - min)); }
}