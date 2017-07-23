#pragma once

#include "ControllerBase.h"
#include <vector>

class Spirit;
class ActionBase;

enum Ditection
{
	Up, Down, Left, Right, Null
};
//auto load map
class ThirdPersionController :public ControllerBase
{
private:
	std::vector<std::pair<std::shared_ptr<Spirit>, std::shared_ptr<ActionBase>>> m_tileMapList;

	Ditection m_ditection = Null;

public:
	ThirdPersionController(std::shared_ptr<SceneBase>);

	void onTick(double tick) override;
};