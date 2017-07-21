
#include "ControllerBase.h"

ControllerBase::ControllerBase(std::shared_ptr<SceneBase> scene) :m_scene(scene)
{
	m_keyAction = application.keyEvent += std::function<void(int, KeyAction)> ([&](int keyCode, KeyAction keyAction)
	{
		onKey(keyCode, keyAction);
	});
}

ControllerBase::~ControllerBase()
{
	application.keyEvent -= m_keyAction;
}