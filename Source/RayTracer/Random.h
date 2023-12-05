#pragma once
#include <random>
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
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
inline glm::vec3 RandomVec3(const glm::vec3& min, const glm::vec3& max)
{
	return glm::vec3(Randomf(min.x, max.x), Randomf(min.y, max.y), Randomf(min.z, max.z));
}
inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	do
	{
		v = RandomVec3({ -1, -1, -1 }, { 1, 1, 1 });
	} while (glm::length2(v) >= 1);
	return v;
}