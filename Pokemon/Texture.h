#pragma once

#include <memory>
#include <SDL.h>
#include <tuple>
#include <vector>

class Texture
{
private:
	//texture ID
	unsigned short m_animationID = 0;

	uint32_t m_lastRefreshTick = 0;

	//texture list
	std::vector <std::tuple<SDL_Texture*, SDL_Rect, uint32_t>> m_textureList;

public:
	Texture(SDL_Renderer* sdlRenderer, const char* fileName);
	void renderCopyTo(SDL_Renderer* sdlRenderer, std::tuple<float, float, float, float> texRect, SDL_Rect rect);
};