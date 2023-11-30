#include "Canvas.h"
#include "SDL.h"
#include "Renderer.h"
Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	size = glm::ivec2(width, height);
	buffer.resize(width * height);
	texture = SDL_CreateTexture(renderer.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

Canvas::~Canvas()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}

void Canvas::Update()
{
	SDL_UpdateTexture(texture, NULL, buffer.data(), size.x * sizeof(rgba_t));
}

void Canvas::Clear(const color4_t& color)
{
	std::fill(buffer.begin(), buffer.end(), ColorToRGBA(color));
}
void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
	if (point.x < 0 || point.x >= size.x || point.x > size.x || point.y >= size.y) return;
	buffer[point.x + (point.y * size.x)] = ColorToRGBA(color);
}