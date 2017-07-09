
#include "SceneBase.h"
#include "Application.h"
#include <SDL.h>

void SceneBase::drawSquare(Square square)
{
	SDL_Rect dRect = SDL_Rect();
	dRect.x = square.dx;
	dRect.x = square.dy;

	SDL_Rect sRect = SDL_Rect();
	sRect.x = square.sx;
	sRect.x = square.sy;

	SDL_RenderCopy(application.getRenderer(), square.texture, &sRect, &dRect);
}

void SceneBase::addSquare(int sx, int sy, int dx, int dy, const char* textureName)
{
	Square newSquare = Square(sx, sy, dx, dy, application.getResourceContent().get<SDL_Texture>(textureName));

	m_squareList.emplace_back(newSquare);

	drawSquare(newSquare);
}