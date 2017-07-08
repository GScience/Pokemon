#pragma once

#include <functional>

class Application
{
private:
	//program title
	const char* m_title;

public:
	//run the program
	void run();

	//init
	Application(const char* title) :m_title(title) {}
};