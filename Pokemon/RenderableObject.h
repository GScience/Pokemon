#pragma once

#include "BaseEngine.h"
#include <tuple>
#include <SDL.h>

class Texture;

class RenderableObject
{
protected:
	//sdl renderer
	SDL_Renderer*	m_sdlRenderer;
	//rect info
	SDL_Rect		m_rect;

	//texture
	Texture*		m_texture		= nullptr;
	//texture rect
	std::tuple<float, float, float, float>		m_textureRect = std::make_tuple(0.0f, 0.0f, 1.0f, 1.0f);

	//visiable
	bool m_visiable = true;

	//order
	unsigned short m_zOrder = 0;

	//object creator
	void*		m_creator;

	RenderableObject(void* creator, SDL_Renderer* sdlRenderer) : m_rect{ 0,0,Setting::windowWidth,Setting::windowHeight }, m_sdlRenderer(sdlRenderer) {}

public:
	bool isCoveredBy(const RenderableObject& sc) const { return m_zOrder < sc.m_zOrder; }
	bool isVisiable() const { return m_visiable; }

	void setVisiable(bool canSee)					{ m_visiable = canSee; }
	void setLocation(int x, int y)					{ m_rect.x = x; m_rect.y = y; }
	void setSize(int width, int height)				{ m_rect.h = height; m_rect.w = width; }
	void setTexture(Texture* texture)				{ m_texture = texture; }
	void setTexPos(float x1, float y1, float x2, float y2)	
	{ 
		std::get<0>(m_textureRect) = x1; 
		std::get<1>(m_textureRect) = y1; 
		std::get<2>(m_textureRect) = y2 - y1; 
		std::get<3>(m_textureRect) = x2 - x1; 
	}

	const int getX() const		{ return m_rect.x; }
	const int getY() const		{ return m_rect.y; }
	const int getHeight()	const	{ return m_rect.h; }
	const int getWidth()	const	{ return m_rect.w; }

	//update
	virtual void update(double) = 0;

	//draw
	virtual void draw() = 0;
};