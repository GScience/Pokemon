#pragma once

#include "Spirit.h"
#include <list>
#include <SDL_image.h>

class SceneBase
{
private:
	std::list<Spirit> m_spiritList;
protected:
	//sdl renderer
	SDL_Renderer* m_sdlRenderer;

	//add square
	Spirit* addSpirit(unsigned short zOrder);

public:
	virtual void initialize() = 0;
	
	void update();

	SceneBase(SDL_Renderer* sdlRenderer) :m_sdlRenderer(sdlRenderer) {}
};

#define SceneCtor using SceneBase::SceneBase