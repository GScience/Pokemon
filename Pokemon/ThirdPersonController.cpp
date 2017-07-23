
#include "ThirdPersionController.h"
#include "Spirit.h"
#include "SceneBase.h"
#include "Move.h"
#include "TileMap.h"
#include "BaseEngine.h"
#include <iostream>
#include <SDL.h>

void ThirdPersionController::onTick(double tick)
{
	if (m_ditection == Up)
	{
		if (!application.getKeyState(SDL_SCANCODE_UP))
		{
			for (auto& spirit : m_tileMapList)
				spirit.second->stop();
			m_ditection = Null;
		}
	}
	else if (m_ditection == Down)
	{
		if (!application.getKeyState(SDL_SCANCODE_DOWN))
		{
			for (auto& spirit : m_tileMapList)
				spirit.second->stop();
			m_ditection = Null;
		}
	}
	else if (m_ditection == Left)
	{
		if (!application.getKeyState(SDL_SCANCODE_LEFT))
		{
			for (auto& spirit : m_tileMapList)
				spirit.second->stop();
			m_ditection = Null;
		}
	}
	else if (m_ditection == Right)
	{
		if (!application.getKeyState(SDL_SCANCODE_RIGHT))
		{
			for (auto& spirit : m_tileMapList)
				spirit.second->stop();
			m_ditection = Null;
		}
	}
	else
	{
		if (application.getKeyState(SDL_SCANCODE_UP))
		{
			for (auto& spirit : m_tileMapList)
				if (spirit.second == nullptr || spirit.second->hasFinished())
					spirit.second = m_scene->addActionTo<Action::MoveWithStep<256, 90, 60>>(spirit.first);
			m_ditection = Up;
		}
		else if (application.getKeyState(SDL_SCANCODE_DOWN))
		{
			for (auto& spirit : m_tileMapList)
				if (spirit.second == nullptr || spirit.second->hasFinished())
					spirit.second = m_scene->addActionTo<Action::MoveWithStep<256, 270, 60>>(spirit.first);
			m_ditection = Down;
		}
		if (application.getKeyState(SDL_SCANCODE_LEFT))
		{
			for (auto& spirit : m_tileMapList)
				if (spirit.second == nullptr || spirit.second->hasFinished())
					spirit.second = m_scene->addActionTo<Action::MoveWithStep<256, 0, 60>>(spirit.first);
			m_ditection = Left;
		}
		else if (application.getKeyState(SDL_SCANCODE_RIGHT))
		{
			for (auto& spirit : m_tileMapList)
				if (spirit.second == nullptr || spirit.second->hasFinished())
					spirit.second = m_scene->addActionTo<Action::MoveWithStep<256, 180, 60>>(spirit.first);
			m_ditection = Right;
		}

	}
}

ThirdPersionController::ThirdPersionController(std::shared_ptr<SceneBase> scene) :ControllerBase(scene)
{
	m_tileMapList.push_back(std::make_pair(application.getResourceContent().get<TileMap>("Resources\\MapRes\\test.tm")->bindToScene(scene), nullptr));
}