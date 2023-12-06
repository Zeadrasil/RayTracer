#include "Material.h"
#include "Random.h"
#include "MathUtils.h"
bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered)
{
    glm::vec3 target = raycastHit.normal + raycastHit.point + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - raycastHit.point);
    scattered.origin = raycastHit.point;
    scattered.direction = direction;
    color = albedo;
    return true;
}
bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered)
{
    glm::vec3 reflected = reflect(ray.direction, raycastHit.normal);

    // set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
    // a mirror has a fuzz value of 0 and a diffused metal surface a higher value
    scattered = ray_t{ raycastHit.point, reflected + randomInUnitSphere() * fuzz };
    color = albedo;
    // make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
    return glm::dot(scattered.direction, raycastHit.normal) > 0;
}