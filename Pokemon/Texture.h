#pragma once

#include <SDL.h>
#include <tuple>
#include <vector>

class Texture
{
private:
	//texture ID
	unsigned short m_animationID;

	//texture list
	std::vector <std::tuple<SDL_Texture*, SDL_Rect>> m_textureList;

public:
	Texture(SDL_Renderer* sdlRenderer, const char* fileName);
	void renderCopyTo(SDL_Renderer* sdlRenderer, SDL_Rect texRect, SDL_Rect rect);
};