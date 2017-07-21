
#include "ThirdPersionController.h"
#include "Spirit.h"
#include "SceneBase.h"
#include "Move.h"
#include "TileMap.h"
#include "BaseEngine.h"
#include <SDL.h>

void ThirdPersionController::onKey(int keyCode, KeyAction action)
{
	if (m_action.get() != nullptr && !m_action->hasFinished())
		return;

	if (keyCode == SDLK_UP)
		for (auto spirit : m_tileMapList)
		{
			m_action = m_scene->addActionTo<Action::Move<128, 0, MAX_HEIGHT / 10>>(spirit);
		}
	else if (keyCode == SDLK_DOWN)
		for (auto spirit : m_tileMapList)
		{
			m_action = m_scene->addActionTo<Action::Move<128, 0, -MAX_HEIGHT / 10>>(spirit);
		}
	if (keyCode == SDLK_LEFT)
		for (auto spirit : m_tileMapList)
		{
			m_action = m_scene->addActionTo<Action::Move<128, MAX_HEIGHT / 10, 0>>(spirit);
		}
	else if (keyCode == SDLK_RIGHT)
		for (auto spirit : m_tileMapList)
		{
			m_action = m_scene->addActionTo<Action::Move<128, -MAX_HEIGHT / 10, 0>>(spirit);
		}
}

ThirdPersionController::ThirdPersionController(std::shared_ptr<SceneBase> scene) :ControllerBase(scene)
{
	m_tileMapList.push_back(application.getResourceContent().get<TileMap>("Resources\\MapRes\\test.tm")->bindToScene(scene));
}