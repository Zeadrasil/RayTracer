#pragma once
#include <string>
#include "SDL.h"
class Canvas;
class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
	friend Canvas;
	void PresentCanvas(const Canvas& canvas);
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

