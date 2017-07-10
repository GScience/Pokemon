
#include "SceneBase.h"
#include "Application.h"
#include <algorithm>
#include <SDL.h>

Spirit* SceneBase::addSpirit()
{
	m_spiritList.emplace_back(Spirit(this, m_sdlRenderer));

	return &m_spiritList.back();
}

void SceneBase::update()
{
	SDL_RenderClear(m_sdlRenderer);

	//sort spirit first
	m_spiritList.sort([](const Spirit spirit1, const Spirit spirit2) { return spirit1.isCoveredBy(spirit2); });

	for (auto spirit : m_spiritList)
		spirit.draw();

	SDL_RenderPresent(m_sdlRenderer);
}