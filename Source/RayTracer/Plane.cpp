#include "Plane.h"
#include "MathUtils.h"
bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit)
{
    // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane
    // the dot product is 0 if the two vectors are perpendicular (90 degrees)
    float denominator = dot(ray.direction, normal);
    if (approximately(denominator, 0.0f))
    {
        return false; // ray direction and plane parallel, no intersection
    }

    // get t (distance) along ray direction to hit point
    float t = glm::dot(center - ray.origin, normal) / denominator;
    if (t < 0)
    {
        return false; // plane behind ray's origin, no intersection
    }

    // check if t is outside min and max distance
    if (t >= maxDistance || t <= minDistance)
    {
        return false;
    }

    // set raycast hit 
    raycastHit.distance = t;
    raycastHit.point = ray.At(raycastHit.distance);
    raycastHit.normal = glm::normalize(normal);
    raycastHit.material = GetMaterial();

    return true;
}