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

	Scene scene = Scene(20); // sky color could be set with the top and bottom color
	
	scene.SetCamera(camera);
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);
	for (int i = 0; i < 0; i++)
	{
		auto material = Random(2) == 1 ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ Randomf(-7.5f, 7.5f), Randomf(-7.5f, 7.5f), Randomf(-15, -5)}, Randomf(0.5f, 5.0f), material);
		scene.AddObject(std::move(sphere));
	}
	auto material = std::make_shared<Lambertian>(color3_t{ 0.8f, 0.8f, 0.8f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1.0f, 0 }, glm::vec3{ 0, 1, 0 }, material);
	//scene.AddObject(std::move(plane));
	material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	auto triangle = std::make_unique<Triangle>(glm::vec3(-1, -1, -3), glm::vec3(1, -1, -3), glm::vec3(0, 1, -3), material);
	scene.AddObject(std::move(triangle));
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