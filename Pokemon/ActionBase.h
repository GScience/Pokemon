#pragma once

#include <SDL.h>
#include "Spirit.h"

class ActionBase
{
private:
	Spirit* m_spirit;

protected:
	ActionBase(Spirit* spirit) :m_spirit(spirit) {}

	const SDL_Rect getRect() { return m_spirit->m_rect; }
public:
	virtual void update(double passedTime) = 0;
};

#define ActionCtor using ActionBase::ActionBase