#pragma once

#include "RenderableObject.h"
#include <SDL.h>

class SpiritComponent final :public RenderableObject
{
	friend class Spirit;

private:
	const SDL_Rect& m_spiritRect;
	SDL_Rect m_scRect;

	void update(double passedTime) override;
	void draw() override;

public:
	SpiritComponent(Spirit* spirit, const SDL_Rect& spiritRect, SDL_Renderer* sdlRenderer) :RenderableObject(spirit, sdlRenderer), m_spiritRect(spiritRect) {}
};
