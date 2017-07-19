
#include "TileMap.h"
#include "Spirit.h"
#include "Application.h"
#include <fstream>
#include <json\json.h>

Tile::Tile(const char* fileName)
{
	std::ifstream file(fileName);
	Json::Value mapInfo;
	file >> mapInfo;

	const char* textureFileName = mapInfo["tile_info"]["texture_name"].asCString();
	m_texture = application.getResourceContent().getTexture(textureFileName);
}

TileMap::TileMap(const char* fileName)
{
	ResourceContent& resContent = application.getResourceContent();

	//read json
	std::ifstream file(fileName);
	Json::Value mapInfo;
	file >> mapInfo;

	Json::Value tileList = mapInfo["tile_list"];

	for (unsigned int i = 0; i < tileList.size(); i++)
	{
		//find tile
		const char* tileFileName = tileList[i]["name"].asCString();
		Tile* tile = resContent.tryGet<Tile>(tileFileName);

		if (tile == nullptr)
			tile = resContent.add<Tile>(tileFileName, tileFileName);

	}
}

void bindToScene(SceneBase* scene)
{
	for (unsigned short x=0;x<15;x++)
		for (unsigned short y = 0; y < 10; y++)
		{

		}
}