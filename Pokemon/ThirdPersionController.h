#pragma once

#include "ControllerBase.h"
#include <vector>

class Spirit;
class ActionBase;

//auto load map
class ThirdPersionController :public ControllerBase
{
private:
	std::vector<std::shared_ptr<Spirit>> m_tileMapList;
	std::shared_ptr<ActionBase> m_action;

public:
	ThirdPersionController(std::shared_ptr<SceneBase>);

	void onKey(int keyCode, KeyAction action);
};