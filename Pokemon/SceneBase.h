#pragma once

#include <list>
#include <SDL_image.h>

class SceneBase
{
private:
	struct Square
	{
		const int sx;
		const int sy;
		const int dx;
		const int dy;
		SDL_Texture* texture;

		Square(int sx, int sy, int dx, int dy, SDL_Texture* texture) :sx(sx), sy(sy), dx(dx), dy(dy), texture(texture) {}
	};
	std::list<Square> m_squareList;

	//only draw
	void drawSquare(Square square);

protected:
	//add square
	void addSquare(int sx, int sy, int dx, int dy, const char* textureName);

public:
	virtual void initialize() = 0;
};