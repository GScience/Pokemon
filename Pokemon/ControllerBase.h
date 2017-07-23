#pragma once

#include "Application.h"
#include <memory>
#include <functional>

class SceneBase;

class ControllerBase
{
private:
	Event<int, KeyAction>::Function m_keyAction;
	Event<double>::Function			m_tickAction;

	bool m_isEnable = true;

protected:
	std::shared_ptr<SceneBase> m_scene;

public:
	bool isEnable() { return m_isEnable; }
	void setEnable(bool isEnable) { m_isEnable = isEnable; }

	virtual void onKey(int key, KeyAction action) {}
	virtual void onTick(double tick) {}

	ControllerBase(std::shared_ptr<SceneBase> scene);
	~ControllerBase();
};