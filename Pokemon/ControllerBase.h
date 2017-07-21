#pragma once

#include "Application.h"
#include <functional>

class ControllerBase
{
private:
	Event<int, KeyAction>::Function m_keyAction;

public:
	virtual void onKey(int key, KeyAction action) = 0;

	ControllerBase();
	~ControllerBase();
};