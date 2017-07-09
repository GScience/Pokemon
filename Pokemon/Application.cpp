
#include "Application.h"

void Application::run()
{
	//init and create window
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(512, 512, SDL_WINDOW_OPENGL |SDL_WINDOW_HIDDEN, &m_sdlWindow, &m_renderer);
	SDL_Texture* texture = IMG_LoadTexture(m_renderer, "Resources\\Logo.png");

	SDL_ShowWindow(m_sdlWindow);

	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
	
	m_resContent.initialize();

	m_nowScene->initialize();

	//listen event
	SDL_Event sdlEvent = SDL_Event();

	while (sdlEvent.type != SDL_QUIT)
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

	SDL_Quit();
}