
#include "Application.h"
#include "SceneBase.h"
#include "Move.h"
#include "TileMap.h"
#include "ControllerBase.h"
#include "Spirit.h"
#include "ThirdPersionController.h"
#include <iostream>
#include <string>

using namespace std;

int id = 0;

class testScene : public SceneBase
{
	SceneCtor;

	std::shared_ptr<Spirit> testSpirit1 = addSpirit(0);
	std::shared_ptr<SpiritComponent> sp;
	std::shared_ptr<Spirit> mapSpirit;

public:
	void test1()
	{
		if (testSpirit1->getX() == 0)
			addActionTo<Action::MoveTo<362, MAX_WIDTH - 256, MAX_HEIGHT - 256>>(testSpirit1)->onFinish += std::function<void()>([this]() { test1(); });
		else
			addActionTo<Action::MoveTo<362, 0, 0>>(testSpirit1)->onFinish += std::function<void()>([this]() { test1(); });
	}
	void test2()
	{
		if (sp->getY() == 0)
			addActionTo<Action::MoveTo<30, 0, 5>>(sp)->onFinish += std::function<void()>([this]() { test2(); });
		else
			addActionTo<Action::MoveTo<30, 0, 0>>(sp)->onFinish += std::function<void()>([this]() { test2(); });
	}
	void initialize() override
	{
		sp = testSpirit1->addSpiritComponent(0);
		sp->setTexture(application.getResourceContent().getTexture("Resources\\PokemonIcon\\1.tex"));
		sp->setTexPos(0, 0, 1, 1);
		sp->setLocation(0, 0);
		sp->setSize(128, 128);

		//test1();
		//test2();

		//mapSpirit = application.getResourceContent().get<TileMap>("Resources\\MapRes\\test.tm")->bindToScene(this);
		application.bindController<ThirdPersionController>();
		/*
		addActionTo<Action::MoveTo<128, 0, -480>>(mapSpirit)->onFinish += std::function<void()>([&]
		{
			addActionTo<Action::MoveTo<128, -256, -480>>(mapSpirit);
		});*/
	}
	int zOrder = 0;
	double totalTime = 0;

	void update(double time) override
	{
		SceneBase::update(time);
		
		totalTime += time;

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