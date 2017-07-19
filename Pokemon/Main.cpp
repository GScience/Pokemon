
#include "Application.h"
#include "SceneBase.h"
#include "Move.h"
#include "TileMap.h"
#include "Spirit.h"
#include <string>

using namespace std;

int id = 0;

class testScene : public SceneBase
{
	SceneCtor;

	Spirit* testSpirit1 = addSpirit(0);
	SpiritComponent* testSC1;

public:
	void test1()
	{
		if (testSpirit1->getX() == 0)
			addActionTo<Action::Move<362, MAX_WIDTH - 256, MAX_HEIGHT - 256>>(testSpirit1)->onFinish += std::function<void()>([this]() { test1(); });
		else
			addActionTo<Action::Move<362, 0, 0>>(testSpirit1)->onFinish += std::function<void()>([this]() { test1(); });
	}
	void test2()
	{
		if (testSC1->getY() == -50)
			addActionTo<Action::Move<50, 0, 50>>(testSC1)->onFinish += std::function<void()>([this]() { test2(); });
		else
			addActionTo<Action::Move<50, 0, -50>>(testSC1)->onFinish += std::function<void()>([this]() { test2(); });

		testSC1->setVisiable(!testSC1->isVisiable());
	}
	void initialize() override
	{
		SpiritComponent* sp = testSpirit1->addSpiritComponent(0);
		sp->setTexture(application.getResourceContent().getTexture("Resources\\PokemonIcon\\1.tex"));
		sp->setTexPos(0, 0, 1, 1);
		sp->setLocation(0, 0);
		sp->setSize(MAX_WIDTH, MAX_HEIGHT);

		testSpirit1->setLocation(0, 0);
		testSpirit1->setSize(256, 256);
		test1();

		testSC1 = testSpirit1->addSpiritComponent(1);
		testSC1->setTexture(application.getResourceContent().getTexture("Resources\\PokemonIcon\\1.tex"));
		testSC1->setTexPos(0, 0, 1, 1);
		testSC1->setLocation(32, 32);
		testSC1->setSize(MAX_WIDTH, MAX_HEIGHT);

		test2();
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
	application.start();

	return 0;
}