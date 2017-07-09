
#include "Application.h"
#include <SDL.h>
#include <SDL_image.h>

void Application::run()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* sdlWindow;
	SDL_Renderer* render;

	SDL_CreateWindowAndRenderer(512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &sdlWindow, &render);
	SDL_Texture* texture = IMG_LoadTexture(render, "Resources\\test.jpg");

	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, nullptr, nullptr);
	SDL_RenderPresent(render);

	SDL_Event sdlEvent = SDL_Event();

	while (sdlEvent.type != SDL_QUIT)
		while (SDL_PollEvent(&sdlEvent));

	SDL_Quit();
}