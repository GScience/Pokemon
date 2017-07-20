#pragma once

#include "ActionBase.h"
#include "Spirit.h"
#include <memory>
#include <list>
#include <SDL_image.h>

class Spirit;

class SceneBase
{
	friend class Application;
private:
	std::list<std::shared_ptr<Spirit>>	m_spiritList;
	std::list<std::shared_ptr<ActionBase>>	m_actionPool;

protected:
	//sdl renderer
	SDL_Renderer* m_sdlRenderer;

public:
	//add spirit
	std::shared_ptr<Spirit> addSpirit(unsigned short zOrder);

	//remove spirit
	void removeSpirit(std::shared_ptr<Spirit> spirit) { spirit->m_isRemoved = true; }

	//add action
	template <class Action> std::shared_ptr<ActionBase> addActionTo(std::shared_ptr<RenderableObject> obj)
	{
		auto action = std::make_shared<Action>(obj);
		m_actionPool.emplace_back(action);
		return action;
	}

	//called when init
	virtual void initialize() = 0;
	//called when update
	virtual void update(double passedTime);

	SceneBase(SDL_Renderer* sdlRenderer) :m_sdlRenderer(sdlRenderer) {}
};

#define SceneCtor using SceneBase::SceneBase