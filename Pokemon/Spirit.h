#pragma once

#include "SpiritComponent.h"
#include <SDL.h>
#include <list>

class SceneBase;

class Spirit
{
	friend class SceneBase;

private:
	//order
	unsigned short m_zOrder = 0;

	//belong to which scene
	SceneBase*		m_scene;
	SDL_Renderer*	m_sdlRenderer;

	//spirit component list
	std::list<SpiritComponent> m_spiritComponentList;

	void draw();
public:
	Spirit(SceneBase* scene, SDL_Renderer* sdlRenderer) :m_scene(scene) , m_sdlRenderer(sdlRenderer) {}

	bool isCoveredBy(const Spirit& sc) const { return m_zOrder < sc.m_zOrder; }

	SpiritComponent* addSpiritComponent(unsigned short zOrder);
};