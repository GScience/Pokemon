
#include "TileMap.h"
#include "Spirit.h"
#include "Application.h"
#include "SceneBase.h"
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

	//tile list
	std::vector<Tile*>	tileList;

	//map size
	m_mapWidth = mapInfo["map_size"]["width"].asUInt();
	m_mapHeight = mapInfo["map_size"]["height"].asUInt();

	m_tileMap.resize(m_mapWidth * m_mapHeight);

	//read tile list
	for (unsigned int i = 0; i < mapInfo["tile_list"].size(); i++)
	{
		//find tile
		const char* tileFileName = mapInfo["tile_list"][i]["name"].asCString();
		Tile* tile = resContent.tryGet<Tile>(tileFileName);

		if (tile == nullptr)
			tile = resContent.add<Tile>(tileFileName, tileFileName);

		tileList.push_back(tile);
	}

	//read map
	Json::Value tileInfo = mapInfo["map_tile"];

	for (unsigned int i = 0; i < m_mapWidth * m_mapHeight; i++)
	{
		Json::Value tiles = tileInfo[i];

		//read all level
		if (tiles.isArray())
			for (unsigned int j = 0; j < tiles.size(); j++)
				m_tileMap[i].push_back(tileList[tiles[j].asUInt()]);
		else
			m_tileMap[i].push_back(tileList[tiles.asUInt()]);
	}
}

std::shared_ptr<Spirit> TileMap::bindToScene(SceneBase* scene)
{
	std::shared_ptr<Spirit> mapSpirit = scene->addSpirit(0);

	for (unsigned int i = 0; i < m_tileMap.size(); i++)
	{
		unsigned int y = i / m_mapWidth;
		unsigned int x = i % m_mapWidth;

		//level
		for (unsigned int j = 0; j < m_tileMap[i].size(); j++)
		{
			auto spiritComponent = mapSpirit->addSpiritComponent(j);
			spiritComponent->setTexture(m_tileMap[i][j]->getTexture());
			spiritComponent->setLocation(MAX_WIDTH / 15 * x, MAX_HEIGHT / 10 * y);
			spiritComponent->setSize(MAX_WIDTH / 15, MAX_HEIGHT / 10);
		}
	}

	return mapSpirit;
}