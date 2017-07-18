
#include "Texture.h"
#include "Application.h"
#include <fstream>
#include <json\json.h>

SDL_Texture* getSDLTexture(SDL_Renderer* sdlRenderer, const char* resourcePath)
{
	ResourceContent& resContent = application.getResourceContent();
	SDL_Texture* texture = resContent.tryGet<SDL_Texture>(resourcePath);

	if (texture == nullptr)
	{
		texture = IMG_LoadTexture(sdlRenderer, resourcePath);
		resContent.add(texture, resourcePath);
	}

	return texture;
}

void Texture::renderCopyTo(SDL_Renderer* sdlRenderer, SDL_Rect smallTexRect, SDL_Rect rect)
{
	SDL_Rect texRect = std::get<1>(m_textureList[m_animationID]);

	smallTexRect.x += texRect.x;
	smallTexRect.y += texRect.y;

	SDL_RenderCopy(sdlRenderer, std::get<0>(m_textureList[m_animationID]), &smallTexRect, &rect);
}

Texture::Texture(SDL_Renderer* sdlRenderer, const char* fileName) :m_animationID(0)
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

		int x1 = image["rect"]["x1"].asInt();
		int y1 = image["rect"]["y1"].asInt();

		SDL_Rect rect{ x1 ,y1,0,0 };
		SDL_Texture* texture = getSDLTexture(sdlRenderer, fileName);

		m_textureList.push_back(std::make_tuple(texture, rect));
	}
}