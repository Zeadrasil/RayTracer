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
	return a.x * b.x + a.y * b.y + a.z * b.z;
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
inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted)
{
	// normalize the incoming vector (v)
	glm::vec3 nv = glm::normalize(v);

	float dt = dot(nv, n);
	float discriminant = 1 - (index * index) * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = index * (nv - (n * dt)) - (n * std::sqrt(discriminant));
		return true;
	}

	return false;
}
inline float schlick(float cosine, float index)
{
	// calculate specular reflection coefficient, or probability of reflection
	float r0 = (1.0f - index) / (1 + index);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * (float)std::pow((1.0f - cosine), 5);
}