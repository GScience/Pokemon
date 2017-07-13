#pragma once

#include "SpiritComponent.h"
#include "RenderableObject.h"
#include <SDL.h>
#include <list>

class SceneBase;

class Spirit :public RenderableObject
{
	friend class SceneBase;

private:
	//spirit component list
	std::list<SpiritComponent> m_spiritComponentList;

	void update(double passedTime) override;

public:
	Spirit(SceneBase* scene, SDL_Renderer* sdlRenderer) :RenderableObject(scene, sdlRenderer) {}

	SpiritComponent* addSpiritComponent(unsigned short zOrder);
};