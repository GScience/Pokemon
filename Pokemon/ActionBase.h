#pragma once

#include "Event.h"
#include <memory>
#include <SDL.h>

class RenderableObject;

class ActionBase
{
protected:
	std::shared_ptr<RenderableObject> m_obj;

	bool m_isStop = false;

public:
	ActionBase(std::shared_ptr<RenderableObject> obj) :m_obj(obj) {}

	//get renderable object
	std::shared_ptr<RenderableObject> getRenderableObject() { return m_obj; }

	//stop
	virtual void stop() { m_isStop = true; }

	//update
	virtual void update(double passedTime)	= 0;
	//check whether the action is finished
	virtual bool hasFinished() const		= 0;

	//call when finish
	Event<> onFinish;
};