#include "Material.h"
#include "Random.h"
#include "MathUtils.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered)
{
    glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - raycastHit.point);

    scattered = ray_t{ raycastHit.point, direction };
    color = albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered)
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);

    // set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
    // a mirror has a fuzz value of 0 and a diffused metal surface a higher value
    scattered = ray_t{ raycastHit.point, reflected + randomInUnitSphere() * fuzz };
    color = albedo;
    // make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
    float icry = glm::dot(scattered.direction, raycastHit.normal);
    bool piss = icry > 0;
    return piss;
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered)
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);
    glm::vec3 refracted;

    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface ( ray -> | -> normal )
    // ray is going out of object (ray direction is facing in the same direction of the surface normal)
    if (glm::dot(ray.direction, raycastHit.normal) > 0)
    {
        outNormal = -raycastHit.normal;
        ni_over_nt = index;
        cosine = index * glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface ( ray -> | <- normal )
        // ray is going into object (ray direction is facing in the opposite direction of the surface norma)
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / index;
        cosine = -glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }

    // set the probability of the ray being reflected or refracted
    float reflectProbability = 1.0f;
    if (refract(ray.direction, outNormal, ni_over_nt, refracted))
    {
        // use schlick and cosine (angle) to determine if ray is reflected or refracted
        reflectProbability = schlick(cosine, index);
    }

    // create reflected or refracted ray
    scattered = (Randomf() < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };
    color = albedo;

    return true;
}