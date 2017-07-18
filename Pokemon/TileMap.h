#pragma once

#include "Spirit.h"
#include "SceneBase.h"
#include "Application.h"

class TileMap
{
private:
	Spirit*				m_spirit;
	SpiritComponent*	m_spiritComponents[15][10][3];

public:
	TileMap(SceneBase* scene, const char* mapName)
	{
		//create spirit
		m_spirit = scene->addSpirit(0);

		//create spirit component
		for (unsigned short x = 0; x < 15; x++)
			for (unsigned short y = 0; y < 10; y++)
				for (unsigned short zOrder = 0; zOrder < 3; zOrder++)
				{
					m_spiritComponents[x][y][zOrder] = m_spirit->addSpiritComponent(zOrder);
					m_spiritComponents[x][y][zOrder]->setSize(MAX_WIDTH / 15, MAX_HEIGHT / 10);
					m_spiritComponents[x][y][zOrder]->setLocation(x * MAX_WIDTH / 15, y * MAX_HEIGHT / 10);
					m_spiritComponents[x][y][zOrder]->setTexture(application.getTexture("Resources\\MapRes\\GrassGround.tex"));
					m_spiritComponents[x][y][zOrder]->setTexPos(0, 0, 32, 32);
				}
	}
};