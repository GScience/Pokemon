#pragma once

#include "Application.h"
#include <memory>
#include <functional>

class SceneBase;

class ControllerBase
{
private:
	Event<int, KeyAction>::Function m_keyAction;

protected:
	std::shared_ptr<SceneBase> m_scene;

public:
	virtual void onKey(int key, KeyAction action) = 0;

	ControllerBase(std::shared_ptr<SceneBase> scene);
	~ControllerBase();
};