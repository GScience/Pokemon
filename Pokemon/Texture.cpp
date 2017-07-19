
#include "Texture.h"
#include "Application.h"
#include <fstream>
#include <json\json.h>

SDL_Texture* getSDLTexture(SDL_Renderer* sdlRenderer, const char* resourcePath)
{
	ResourceContent &resContent = application.getResourceContent();
	SDL_Texture* texture = resContent.tryGet<SDL_Texture>(resourcePath);

	if (texture == nullptr)
	{
		texture = IMG_LoadTexture(sdlRenderer, resourcePath);
		resContent.add(resourcePath, texture);
	}

	return texture;
}

void Texture::renderCopyTo(SDL_Renderer* sdlRenderer, std::tuple<float, float, float, float> smallTexRect, SDL_Rect rect)
{
	//change image
	if (application.getTime() - m_lastRefreshTick >= std::get<2>(m_textureList[m_animationID]))
	{
		m_lastRefreshTick += application.getTime() - m_lastRefreshTick;
		m_animationID++;

		if (m_animationID == m_textureList.size())
			m_animationID = 0;
	}

	SDL_Rect texRect = std::get<1>(m_textureList[m_animationID]);

	int textureX1 = (int)(std::get<0>(smallTexRect) * texRect.w) + texRect.x;
	int textureY1 = (int)(std::get<1>(smallTexRect) * texRect.h) + texRect.y;

	int textureHeight	= (int)((std::get<2>(smallTexRect) - std::get<0>(smallTexRect)) * texRect.h);
	int textureWidth	= (int)((std::get<3>(smallTexRect) - std::get<1>(smallTexRect)) * texRect.w);

	texRect = { textureX1, textureY1, textureWidth, textureHeight };

	SDL_RenderCopy(sdlRenderer, std::get<0>(m_textureList[m_animationID]), &texRect, &rect);
}

Texture::Texture(SDL_Renderer* sdlRenderer, const char* fileName)
{
	//read json
	std::ifstream file(fileName);
	Json::Value textureInfo;
	file >> textureInfo;

	//close file
	file.close();

	Json::Value imageList = textureInfo["images"];
	
	for (unsigned int imageID = 0; imageID < imageList.size(); imageID++)
	{
		//load a image
		Json::Value image = imageList[imageID];

		const char* fileName = image["fileName"].asCString();
		Uint32 tick = image["keep_tick"].asInt();

		int x1 = image["rect"]["x1"].asInt();
		int x2 = image["rect"]["x2"].asInt();
		int y1 = image["rect"]["y1"].asInt();
		int y2 = image["rect"]["y2"].asInt();

		SDL_Rect textureRect = { x1, y1, x2 - x1, y2 - y1 };
		SDL_Texture* texture = getSDLTexture(sdlRenderer, fileName);

		m_textureList.push_back(std::make_tuple(texture, textureRect, tick));
	}
}