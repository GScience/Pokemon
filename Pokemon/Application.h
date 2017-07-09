#pragma once

#include "Event.h"
#include <SDL_keycode.h>
#include <functional>

enum keyAction { keyDown, keyUp };

class Application
{
private:
	//program title
	const char* m_title;

public:
	//keyboard event(key,action)
	Event<int, keyAction> keyEvent;

	//run the program
	void run();

	//init
	Application(const char* title) :m_title(title) {}
};