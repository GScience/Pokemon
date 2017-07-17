#pragma once

#include "RenderableObject.h"
#include "Event.h"
#include <SDL.h>

class ActionBase
{
protected:
	RenderableObject* m_obj;

public:
	ActionBase(RenderableObject* obj) :m_obj(obj) {}

	//update
	virtual void update(double passedTime)	= 0;
	//check whether the action is finished
	virtual bool hasFinished()				= 0;

	//call when finish
	Event<> onFinish;
};