#include "Camera.h"
Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
    fov{ fov },
    aspectRatio{ aspectRatio }
{
    LookAt(eye, target, up);
}
void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	this->eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)
	forward = glm::normalize(eye - target);
		// use cross product to create vectors
		// right = up x forward 
	right = glm::normalize(cross(up, forward));
		// up = forward x right
	this->up = cross(forward,  right);

	CalculateViewPlane();
}
void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2;
	float width = height * aspectRatio;

	// calculate horizontal vector (right vector * width)
	horizontal = right * width;
		// calculate vertical vector (up vector * height)
	vertical = up * height;
		// calculate lower left location (origin)
	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) - forward;
}
ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// the ray origin is the camera eye
	ray.origin = eye;
		// calculate direction from point
	ray.direction = lowerLeft + (horizontal * point.x) + (vertical * point.y) - eye;

	return ray;
}