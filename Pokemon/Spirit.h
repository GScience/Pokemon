#pragma once

#include "SpiritComponent.h"
#include <SDL.h>
#include <list>

class SceneBase;

class Spirit
{
	friend class SceneBase;
	friend class ActionBase;

private:
	//order
	unsigned short m_zOrder = 0;

	//belong to which scene
	SceneBase*		m_scene;
	SDL_Renderer*	m_sdlRenderer;
	SDL_Rect		m_rect;

	//spirit component list
	std::list<SpiritComponent> m_spiritComponentList;

	void update(double passedTime);

public:
	Spirit(SceneBase* scene, SDL_Renderer* sdlRenderer) :m_scene(scene) , m_sdlRenderer(sdlRenderer), m_rect{ 0,0,512,512 } {}

	bool isCoveredBy(const Spirit& sc) const { return m_zOrder < sc.m_zOrder; }

	void setLocation(int x, int y)		{ m_rect.x = x; m_rect.y = y; }
	void setSize(int width, int height) { m_rect.h = height; m_rect.w = width; }

	SpiritComponent* addSpiritComponent(unsigned short zOrder);
};