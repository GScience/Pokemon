
#include "Application.h"
#include "SceneBase.h"
#include <string>

using namespace std;

int id = 0;

class testScene : SceneBase
{
	SceneCtor(testScene)

public:
	void initialize() override
	{
		addSquare(0, 0, 0, 0, "Resources\\PokemonIcon\\1.png");

		SDL_RenderCopy(m_sdlRenderer, application.getResourceContent().get<SDL_Texture>((((string)"Resources\\PokemonIcon\\1.png").c_str())), nullptr, nullptr);
		SDL_RenderPresent(m_sdlRenderer);
	}
};

int main(int argc, char* args[])
{
	application.initEvent += (std::function<void()>)[]
	{
		application.addScene<testScene>("testScene");
	};
	application.run();

	return 0;
}