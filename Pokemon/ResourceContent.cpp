
#include "ResourceContent.h"
#include "Application.h"
#include "Texture.h"
#include "TileMap.h"
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <io.h>

using namespace std;

void* ResourceContent::loadResource(const char * fileName)
{
	string extensionName = ((string)fileName).substr(((string)fileName).find_last_of('.'));
	std::transform(extensionName.begin(), extensionName.end(), extensionName.begin(), tolower);

	void* pointer = nullptr;

	if (extensionName == ".tex")
	{
		cout << "Load Texture : " << fileName << endl;

		pointer = add<Texture>(fileName, m_sdlRenderer, fileName);
	}
	else if (extensionName == ".tm")
	{
		cout << "Load TileMap : " << fileName << endl;

		pointer = add<TileMap>(fileName, fileName);
	}
	else
		cout << "Pass file    : " << fileName << endl;

	return pointer;
}
void ResourceContent::initResources(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(((string)dir + "\\*.*").c_str(), &findData);
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;

			initResources(((string)dir + "\\" + findData.name).c_str());
		}
		else
		{
			string fileName = (string)dir + "\\" + findData.name;

			//check whether has been load
			if (m_resourceMap.find(fileName) == m_resourceMap.end())
				loadResource(fileName.c_str());
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // 关闭搜索句柄
}

void ResourceContent::initialize(SDL_Renderer* sdlRenderer, const char* path)
{
	m_sdlRenderer = sdlRenderer;
	initResources(path);
}