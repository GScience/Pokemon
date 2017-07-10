#pragma once

#include <SDL.h>

class SpiritComponent
{
	friend class Spirit;

private:
	SDL_Renderer*	m_sdlRenderer;
	Spirit*			m_spirit;
	SDL_Texture*	m_texture;

	SDL_Rect m_dRect = SDL_Rect();
	SDL_Rect m_sRect = SDL_Rect();

	unsigned short m_zOrder = 0;

	//draw
	void draw();
public:
	SpiritComponent(Spirit* spirit, SDL_Renderer* sdlRenderer) :m_sdlRenderer(sdlRenderer), m_spirit(spirit) {}

	void setTexture(SDL_Texture* texture)			{ m_texture = texture; }
	void setLocation(int x, int y)					{ m_dRect.x = x; m_dRect.y = y; }
	void setSize(int width, int height)				{ m_dRect.h = height; m_dRect.w = width; }
	void setTexPos(int x1, int y1, int x2, int y2)	{ m_sRect.x = x1; m_sRect.y = y1; m_sRect.h = y2 - y1; m_sRect.w = x2 - x1; }
	void setZOrder(unsigned short zOrder)			{ m_zOrder = zOrder; }
	
	bool isCoveredBy(const SpiritComponent& sc) const { return m_zOrder < sc.m_zOrder; }
};
