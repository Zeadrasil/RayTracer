#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio);

	void LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up);
	ray_t GetRay(const glm::vec2& point) const;

private:
	void CalculateViewPlane();

private:
	// eye position
	glm::vec3 eye{ 0 };

	// camera axis
	glm::vec3 right{ 0 };
	glm::vec3 up{ 0 };
	glm::vec3 forward{ 0 };

	// view plane origin and horizontal and vertical axis
	glm::vec3 lowerLeft{ 0 };
	glm::vec3 horizontal{ 0 };
	glm::vec3 vertical{ 0 };

	float fov{ 0 }; // field of view (angle is in degrees)
	float aspectRatio{ 0 }; // screen width / screen height (800 / 600 = 1.333)
};

