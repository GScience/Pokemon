
#include "Application.h"
#include "SceneBase.h"
#include <string>

using namespace std;

int id = 0;

class testScene : SceneBase
{
	SceneCtor;

public:
	void initialize() override
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			for (unsigned int j = 0; j < 256; j++)
			{
				Spirit* spirit = addSpirit(i);
				SpiritComponent* sp = spirit->addSpiritComponent(0);
				sp->setTexture(application.getTexture("Resources\\PokemonIcon\\1.png"));
				sp->setTexPos(0, 0, 32, 32);
				sp->setLocation(i, i);
				sp->setSize(256, 256);
			}
		}
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