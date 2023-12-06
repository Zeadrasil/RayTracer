#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "glm/gtx/color_space.hpp"
int main(int argc, char *argv[])
{
	SeedRandom((unsigned int)time(nullptr));
	std::cout << "Hello World!";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Bruh", 400, 300);
	Canvas canvas(400, 300, renderer);
	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene = Scene(8, {0.5f, 0.7f, 1.0f}, {1, 1, 1}); // sky color could be set with the top and bottom color
	
	scene.SetCamera(camera);
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{

			std::shared_ptr<Material> material;

			// create random material
			float r = Randomf();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ Randomf(0.5f, 1.0f) }, Randomf(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, Randomf(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = Randomf(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Randomf(-0.5f, 0.5f), radius - 1, z + Randomf(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
	auto material = std::make_shared<Lambertian>(color3_t{ 0.8f, 0.8f, 0.8f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1.0f, 0 }, glm::vec3{ 0, 1, 0 }, material);
	scene.AddObject(std::move(plane));
	material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	auto triangle = std::make_unique<Triangle>(glm::vec3(-1, -1, -3), glm::vec3(1, -1, -3), glm::vec3(0, 1, -3), material);
	//scene.AddObject(std::move(triangle));
	bool going = true;
	while (going)
	{
		scene.Render(canvas, 10);
		canvas.Update();
		renderer.PresentCanvas(canvas);
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			going = false;
		}
	}
	renderer.Shutdown();
	return 0;
}