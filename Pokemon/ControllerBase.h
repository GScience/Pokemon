#pragma once

#include "Application.h"
#include <functional>

class ControllerBase
{
private:
	void* m_keyAction;

public:
	virtual void onKey(int key, KeyAction action) = 0;

	ControllerBase();
	~ControllerBase();
};