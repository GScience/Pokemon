
#include "Application.h"
#include <SDL.h>
#include <SDL_image.h>

void Application::run()
{
	SDL_Surface* screen = NULL;
	SDL_Surface* hello = NULL;

	SDL_Surface* icon = IMG_Load("Resources\\ICON.ico");

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(512, 512, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption(m_title, m_title);
	SDL_WM_SetIcon(icon, nullptr);

	hello = IMG_Load("Resources\\test.jpg");
	SDL_BlitSurface(hello, NULL, screen, NULL);

	SDL_Flip(screen);
	SDL_Event sdlEvent = SDL_Event();

	while (sdlEvent.type != SDL_QUIT)
		while (SDL_PollEvent(&sdlEvent));

	//SDL_Delay(2000);

	SDL_FreeSurface(hello);

	SDL_Quit();
}