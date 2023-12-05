#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
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
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	for (int i = 0; i < 10; i++)
	{
		auto sphere = std::make_unique<Sphere>(glm::vec3{ Randomf(-7.5f, 7.5f), Randomf(-7.5f, 7.5f), Randomf(-15, -5)}, Randomf(0.5f, 5.0f), material);
		scene.AddObject(std::move(sphere));
	}
	bool going = true;
	while (going)
	{
		scene.Render(canvas);
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