#pragma once

#include "ControllerBase.h"
#include <string>
#include <map>
#include <memory>

class GameModeBase
{
private:
	std::map<std::string, std::unique_ptr<ControllerBase>> m_controllers;

protected:
	std::shared_ptr<SceneBase> m_scene;

	template <class Controller> void bindController()
	{
		if (m_controllers.find(typeid(Controller).name()) != m_controllers.end())
			return;

		m_controllers.emplace(std::make_pair(typeid(Controller).name(), std::make_unique<Controller>(m_scene)));
	}

	template <class Controller> Controller* findController()
	{
		auto result = m_controllers.find(typeid(Controller).name());

		if (result == m_controllers.end())
			return nullptr;

		return reinterpret_cast<Controller*>(result->second.get());
	}

public:
	GameModeBase(std::shared_ptr<SceneBase> scene) :m_scene(scene) {}
};