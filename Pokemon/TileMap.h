#pragma once

#include "Application.h"
#include <Array>
#include <SDL.h>

class Spirit;
class SceneBase;
class Texture;

class Tile
{
private:
	Texture* m_texture;

public:
	Texture* getTexture() const { return m_texture; }

	Tile(const char* fileName);
};

class TileMap
{
private:
	std::vector<std::vector<Tile*>> m_tileMap;

	//map size
	unsigned int m_mapWidth;
	unsigned int m_mapHeight;

public:
	TileMap(const char* fileName);
	std::shared_ptr<Spirit> bindToScene(SceneBase* scene);
};