
#include "Application.h"
#include "SceneBase.h"
#include <string>

using namespace std;

int id = 0;

class testScene :SceneBase
{
public:

	void initialize() override
	{
		addSquare(0, 0, 0, 0, "Resources\\PokemonIcon\\1.png");

		SDL_RenderCopy(application.getRenderer(), application.getResourceContent().get<SDL_Texture>((((string)"Resources\\PokemonIcon\\1.png").c_str())), nullptr, nullptr);
		SDL_RenderPresent(application.getRenderer());
	}
};

void onKey(int key, keyAction action)
{
	//SDL_RenderCopy(application.getRenderer(), application.getResourceContent().get<SDL_Texture>((((string)"Resources\\PokemonIcon\\" + to_string(id) + ".png").c_str())), nullptr, nullptr);
	//SDL_RenderPresent(application.getRenderer());
	
	id++;
}
int main(int argc, char* args[])
{
	application.keyEvent += onKey;
	application.addScene<testScene>("testScene");
	application.run();

	return 0;
}