#pragma once
template<typename T>
inline T lerp(const T& a, const T& b, const T& t)
{
	return a + t * (b - a)
}