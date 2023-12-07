#pragma once
#include "Color.h"
#include "glm/glm.hpp"
#include <vector>
struct SDL_Texture;
class Renderer;
class Canvas
{
public:
	Canvas(int width, int height, const Renderer& renderer);
	~Canvas();

	void Update();

	void Clear(const color4_t& color);
	void DrawPoint(const glm::ivec2& point, const color4_t& color);

	const glm::ivec2 GetSize() const { return size; };
	friend Renderer;
private:
	glm::ivec2 size{ 0 };
	SDL_Texture* texture = nullptr;
	std::vector<rgba_t> buffer;
};

