#pragma once

#include "Spirit.h"
#include "ActionBase.h"
#include <list>
#include <SDL_image.h>

class SceneBase
{
private:
	std::list<Spirit>		m_spiritList;
	std::list<ActionBase*>	m_actionPool;

protected:
	//sdl renderer
	SDL_Renderer* m_sdlRenderer;

public:
	//add spirit
	Spirit* addSpirit(unsigned short zOrder);

	//add action
	template <class Action> Action* addActionTo(RenderableObject* obj)
	{
		Action* action = new Action(obj);
		action->initialize();
		m_actionPool.emplace_back(action);
		return action;
	}

	virtual void initialize() = 0;
	virtual void update(double passedTime);

	SceneBase(SDL_Renderer* sdlRenderer) :m_sdlRenderer(sdlRenderer) {}
};

#define SceneCtor using SceneBase::SceneBase