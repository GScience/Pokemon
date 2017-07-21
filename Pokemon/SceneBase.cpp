
#include "SceneBase.h"
#include "Spirit.h"
#include <vector>
#include <algorithm>
#include <SDL.h>

std::shared_ptr<Spirit> SceneBase::addSpirit(unsigned short zOrder)
{
	std::shared_ptr<Spirit> newSpirit = std::make_shared<Spirit>(this, m_sdlRenderer);
	newSpirit->m_zOrder = zOrder;

	auto i = m_spiritList.begin();

	for (; i != m_spiritList.end(); i++)
		if (!(*i)->isCoveredBy(*newSpirit))
			break;

	return *m_spiritList.emplace(i, newSpirit);
}

void SceneBase::update(double passedTime)
{
	SDL_RenderClear(m_sdlRenderer);

	//save empty action
	std::vector<std::shared_ptr<ActionBase>> removedActionPool;

	//update action
	for (auto& action = m_actionPool.begin(); action != m_actionPool.end(); )
	{
		if ((*action)->hasFinished())
		{
			removedActionPool.push_back(*action);
			action = m_actionPool.erase(action);
		}
		else if ((*action)->getRenderableObject()->isRemoved())
			action = m_actionPool.erase(action);
		else
		{
			(*action)->update(passedTime);
			action++;
		}
	}

	//call finish function
	for (auto action : removedActionPool)
		action->onFinish();
	
	removedActionPool.clear();

	//update action and draw
	for (auto spirit = m_spiritList.begin(); spirit != m_spiritList.end();)
	{
		if ((*spirit)->isRemoved())
			spirit = m_spiritList.erase(spirit);
		else
		{
			(*spirit)->update(passedTime);

			if ((*spirit)->isVisiable())
				(*spirit)->draw();

			spirit++;
		}
	}

	SDL_RenderPresent(m_sdlRenderer);
}