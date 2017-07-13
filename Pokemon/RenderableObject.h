#pragma once

#include <SDL.h>

class RenderableObject
{
private:

protected:
	unsigned short m_zOrder = 0;

	//sdl renderer
	SDL_Renderer*	m_sdlRenderer;
	//rect info
	SDL_Rect		m_rect;
	//texture
	SDL_Texture*	m_texture		= nullptr;
	//texture rect
	SDL_Rect		m_textureRect	= SDL_Rect();

	//object creator
	void*		m_creator;

	RenderableObject(void* creator, SDL_Renderer* sdlRenderer) : m_rect{ 0,0,512,512 }, m_sdlRenderer(sdlRenderer) {}

public:
	bool isCoveredBy(const RenderableObject& sc) const { return m_zOrder < sc.m_zOrder; }

	void setLocation(int x, int y) { m_rect.x = x; m_rect.y = y; }
	void setSize(int width, int height) { m_rect.h = height; m_rect.w = width; }
	void setTexture(SDL_Texture* texture) { m_texture = texture; }
	void setTexPos(int x1, int y1, int x2, int y2) { m_textureRect.x = x1; m_textureRect.y = y1; m_textureRect.h = y2 - y1; m_textureRect.w = x2 - x1; }

	const int getX()		{ return m_rect.x; }
	const int getY()		{ return m_rect.y; }
	const int getHeight()	{ return m_rect.h; }
	const int getWidth()	{ return m_rect.w; }

	//update
	virtual void update(double) = 0;
};