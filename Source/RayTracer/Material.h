#pragma once
#include "Ray.h"
#include "Color.h"
class Material
{
	public:
		virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) = 0;
		virtual color3_t GetEmissive() const { return { 0, 0, 0 }; };
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : albedo{ albedo } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered);

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
class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float index) : albedo{ albedo }, index{ index } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) override;

protected:
	glm::vec3 albedo{ 1 };
	float index{ 1 }; // refraction index
};
class Emissive : public Material
{
public:
	Emissive(const color3_t& albedo, float intensity = 1.0f) : albedo{ albedo }, intensity{ intensity } {}

	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) override { return false; }
	color3_t GetEmissive() const override { return albedo * intensity; }

private:
	glm::vec3 albedo{ 1, 1, 1 };
	float intensity{ 1 };
};