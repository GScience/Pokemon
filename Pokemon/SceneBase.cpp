
#include "SceneBase.h"
#include "Spirit.h"
#include <algorithm>
#include <SDL.h>

Spirit* SceneBase::addSpirit(unsigned short zOrder)
{
	Spirit newSpirit = Spirit(this, m_sdlRenderer);
	newSpirit.m_zOrder = zOrder;

	auto i = m_spiritList.begin();

	for (; i != m_spiritList.end(); i++)
		if (!i->isCoveredBy(newSpirit))
			break;

	return &*m_spiritList.emplace(i, newSpirit);
}

void SceneBase::update(double passedTime)
{
	SDL_RenderClear(m_sdlRenderer);

	//save empty action
	std::vector<std::shared_ptr<ActionBase>> removedActionPool;

	//update action
	for (auto action = m_actionPool.begin(); action != m_actionPool.end(); )
	{
		if ((*action)->hasFinished())
		{
			removedActionPool.push_back(*action);
			action = m_actionPool.erase(action);
		}
		else
		{
			(*action)->update(passedTime);
			action++;
		}
	}

	//call finish function
	for (auto action : removedActionPool)
		action->onFinish();
	
	//update action and draw
	for (auto& spirit : m_spiritList)
	{
		spirit.update(passedTime);
		
		if (spirit.isVisiable())
			spirit.draw();
	}

	SDL_RenderPresent(m_sdlRenderer);
}