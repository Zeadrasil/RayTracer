#pragma once
#include "Ray.h"
#include "Color.h"
class Material
{
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : albedo{ albedo } {}
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered);

protected:
	color3_t albedo;
};
class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : albedo{ albedo }, fuzz{ fuzz } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered)  override;

protected:
	glm::vec3 albedo{ 0 };
	float fuzz = 0;
};
