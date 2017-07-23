
#include "ControllerBase.h"

ControllerBase::ControllerBase(std::shared_ptr<SceneBase> scene) :m_scene(scene)
{
	m_keyAction = application.keyEvent += std::function<void(int, KeyAction)> ([&](int keyCode, KeyAction keyAction)
	{
		if (isEnable())
			onKey(keyCode, keyAction);
	});

	m_tickAction = application.tickEvent += std::function<void(double)>([&](double tick)
	{
		if (isEnable())
			onTick(tick);
	});
}

ControllerBase::~ControllerBase()
{
	application.keyEvent -= m_keyAction;
	application.tickEvent -= m_tickAction;
}