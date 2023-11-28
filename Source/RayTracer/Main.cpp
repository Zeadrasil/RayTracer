#include <iostream>
#include "Renderer.h"
int main(int argc, char *argv[])
{
	std::cout << "Hello World!";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Bruh", 400, 300);

	bool going = true;
	while (going)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
		{
			going = false;
			break;
		}
		}
	}
	renderer.Shutdown();
	return 0;
}