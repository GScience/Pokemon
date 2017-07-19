#pragma once

#include "Application.h"
#include <Array>
#include <SDL.h>

class SceneBase;
class Texture;

class Tile
{
private:
	Texture* m_texture;

public:
	Tile(const char* fileName);
};

class TileMap
{
private:
	std::array<std::vector<Tile>, 150> tileArray;

public:
	TileMap(const char* fileName);
	void bindToScene(SceneBase* scene);
};