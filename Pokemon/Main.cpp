
#include "Application.h"
#include "SceneBase.h"
#include "Move.h"
#include <string>

using namespace std;

int id = 0;

class testScene : SceneBase
{
	SceneCtor;

public:
	void initialize() override
	{
		for (unsigned int i = 0; i < 1; i++)
		{
			Spirit* spirit = addSpirit(i);
			SpiritComponent* sp = spirit->addSpiritComponent(0);
			sp->setTexture(application.getTexture("Resources\\PokemonIcon\\1.png"));
			sp->setTexPos(0, 0, 32, 32);
			sp->setLocation(0, 0);
			sp->setSize(512, 512);

			spirit->setLocation(i * 32, i * 32);
			spirit->setSize(256, 256);
			addActionTo<Action::Move<128, 256, 256>>(spirit)->onFinish += std::function<void()>(
				[this, spirit]
				{
					this->addActionTo<Action::Move<128, 0, 0>>(spirit);
				}
			);
		}
	}
	int zOrder = 0;
	double totalTime = 0;

	void update(double time) override
	{
		SceneBase::update(time);
		
		totalTime += time;

		if (totalTime < 1)
			return;

		totalTime = 0;

		if (zOrder == 256)
			zOrder = 0;

		/*Spirit* testSpirit = addSpirit(zOrder);

		SpiritComponent* sp = testSpirit->addSpiritComponent(0);
		sp->setTexture(application.getTexture("Resources\\PokemonIcon\\1.png"));
		sp->setTexPos(0, 0, 32, 32);
		sp->setLocation(0, 0);
		sp->setSize(1024, 1024);

		testSpirit->setLocation(-1024, -1024);
		testSpirit->setSize(1024, 1024);

		zOrder++;*/
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