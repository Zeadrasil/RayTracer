#pragma once
template<typename T>
inline T lerp(const T& a, const T& b, float t)
{
	return a + t * (b - a);
}
inline glm::vec3 cross(const glm::vec3& a, const glm::vec3& b)
{
	return { (float)( a.y * b.z - b.y * a.z), (float)(a.z * b.x - b.z - a.x), (float)(a.x * b.y - b.x * a.y) };
}
inline float dot(const glm::vec3& a, const glm::vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z + b.z;
}
inline glm::vec3 reflect(glm::vec3 v, glm::vec3 n)
{
	return v - 2.0f * dot(n, v) * n;
}
inline bool approximately(float value1, float value2)
{
	return abs(value1 - value2) < FLT_EPSILON;
}
inline bool approximately(float value1, float value2, float errorMargin)
{
	return abs(value1 - value2) < errorMargin;
}