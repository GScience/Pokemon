
#include "Application.h"
#include "BaseEngine.h"
#include "SceneBase.h"
#include <iostream>

void Application::run()
{
	//init and create window
	SDL_Init(SDL_INIT_EVERYTHING);

	m_sdlWindow		= SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Setting::windowWidth, Setting::windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	m_sdlRenderer	= SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	
	SDL_Texture* texture = IMG_LoadTexture(m_sdlRenderer, "Resources\\Logo.png");

	SDL_ShowWindow(m_sdlWindow);

	SDL_RenderClear(m_sdlRenderer);
	SDL_RenderCopy(m_sdlRenderer, texture, nullptr, nullptr);
	SDL_RenderPresent(m_sdlRenderer);
	
	//load resources
	m_resContent.initialize(m_sdlRenderer, "Resources");
	
	//init
	initEvent();

	while (m_nowScene == nullptr);

	//listen event
	SDL_Event sdlEvent = SDL_Event();

	uint32_t lastCallTime = SDL_GetTicks();

	//main loop
	while (sdlEvent.type != SDL_QUIT)
	{
		m_nowTime = SDL_GetTicks();
		m_nowScene->update((m_nowTime - lastCallTime) / 1000.0);
		tickEvent((m_nowTime - lastCallTime) / 1000.0);
		lastCallTime = m_nowTime;

		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_KEYDOWN:
				keyEvent(sdlEvent.key.keysym.sym, keyDown);
				break;
			case SDL_KEYUP:
				keyEvent(sdlEvent.key.keysym.sym, keyUp);
				break;
			default:
				break;
			}
		}
	}
}

void Application::start()
{
#ifdef _DEBUG
	run();
#else
	try
	{
		run();
	}
	catch (std::exception)
	{
		SDL_Quit();
	}
#endif
}