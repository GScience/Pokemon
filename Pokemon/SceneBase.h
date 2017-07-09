#pragma once

#include <list>
#include <SDL_image.h>

class SceneBase
{
private:
	//test
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
	//test end

	//only draw
	void drawSquare(Square square);

protected:
	//sdl renderer
	SDL_Renderer* m_sdlRenderer;

	//add square
	void addSquare(int sx, int sy, int dx, int dy, const char* textureName);

public:
	virtual void initialize() = 0;

	SceneBase(SDL_Renderer* sdlRenderer) :m_sdlRenderer(sdlRenderer) {}
};

#define SceneCtor(ClassName) public: ClassName(SDL_Renderer* sdlRenderer) :SceneBase(sdlRenderer) {} private: