
#include "SceneBase.h"
#include "Application.h"
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

	for (auto action = m_actionPool.begin(); action != m_actionPool.end(); )
	{
		if ((*action)->hasFinished())
		{
			(*action)->onFinish();
			delete *action;
			action = m_actionPool.erase(action);
		}
		else
		{
			(*action)->update(passedTime);
			action++;
		}
	}

	for (auto& spirit : m_spiritList)
		spirit.update(passedTime);

	SDL_RenderPresent(m_sdlRenderer);
}