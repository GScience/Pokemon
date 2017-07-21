
#include "ControllerBase.h"

ControllerBase::ControllerBase()
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