#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
int main(int argc, char *argv[])
{
	SeedRandom((unsigned int)time(nullptr));
	std::cout << "Hello World!";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Bruh", 400, 300);
	Canvas canvas(400, 300, renderer);
	bool going = true;
	while (going)
	{
		canvas.Clear({0, 0, 0, 1});
		for (int i = 0; i < 1000; i++)
		{
			canvas.DrawPoint({ Random(400), Random(300)}, {Randomf(), Randomf(), Randomf(), 1});
		}
		renderer.PresentCanvas(canvas);
		canvas.Update();
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