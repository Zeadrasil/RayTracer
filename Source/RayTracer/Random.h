#pragma once
#include <random>
inline void SeedRandom(unsigned int seed)
{
	srand(seed);
}
inline int Random()
{
	return rand();
}
inline float Randomf()
{
	return float(Random() / (float)RAND_MAX);
}
inline int Random(int max)
{
	return Random() % max;
}
inline float Randomf(float max)
{
	return Randomf() * max;
}
inline int Random(int min, int max)
{
	return (min < max) ? (Random() % (max - min)) + min : (min + max) / 2;
}
inline float Randomf(float min, float max)
{
	return (min < max) ? (Randomf() * (max - min)) + min : (min + max) / 2.0f;
}