#pragma once
#include "Color.h"
#include "Canvas.h"
#include "Ray.h"
#include "Object.h"
#include <memory>
class Camera;
class Scene
{
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		topColor{ topColor },
		bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas);
	color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit);
	void AddObject(std::unique_ptr<Object> object) { objects.push_back(std::move(object)); }

	void SetCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }

private:
	std::shared_ptr<Camera> camera;
	std::vector<std::unique_ptr<Object>> objects;
	color3_t topColor{ 0 };
	color3_t bottomColor{ 1 };
};

