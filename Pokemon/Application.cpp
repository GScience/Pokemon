
#include "Application.h"

void Application::run()
{
	//init and create window
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(512, 512, SDL_WINDOW_OPENGL |SDL_WINDOW_HIDDEN, &m_sdlWindow, &m_sdlRenderer);
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

	m_nowScene->initialize();

	//listen event
	SDL_Event sdlEvent = SDL_Event();

	while (sdlEvent.type != SDL_QUIT)
	{
		m_nowScene->update();

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

	SDL_Quit();
}