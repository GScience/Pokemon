#pragma once

#include "SpiritComponent.h"
#include "RenderableObject.h"
#include <memory>
#include <SDL.h>
#include <list>

class SceneBase;

class Spirit :public RenderableObject
{
	friend class SceneBase;

private:
	//spirit component list
	std::list<std::shared_ptr<SpiritComponent>> m_spiritComponentList;

	void update(double passedTime) override;
	void draw()	override;

public:
	Spirit(SceneBase* scene, SDL_Renderer* sdlRenderer) :RenderableObject(scene, sdlRenderer) {}

	//add component object
	std::shared_ptr<SpiritComponent> addSpiritComponent(unsigned short zOrder);

	//remove spirit
	void removeSpiritComponent(std::shared_ptr<SpiritComponent> spiritComponent) { spiritComponent->m_isRemoved = true; }
};