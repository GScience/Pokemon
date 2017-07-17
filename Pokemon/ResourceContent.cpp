
#include "ResourceContent.h"
#include "Application.h"
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <io.h>

using namespace std;

void ResourceContent::loadResources(const char * dir)
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

			loadResources(((string)dir + "\\" + findData.name).c_str());
		}
		else
		{
			string fileName = (string)dir + "\\" + findData.name;
			string extensionName = fileName.substr(fileName.find_last_of('.'));
			std::transform(extensionName.begin(), extensionName.end(), extensionName.begin(), tolower);

			if (extensionName == ".png" || extensionName == ".jpg" || extensionName == ".gif" || extensionName == ".bmp" || extensionName == ".ico")
				add<SDL_Texture>(IMG_LoadTexture(m_sdlRenderer, fileName.c_str()), fileName.c_str());

			cout << "Load file " << findData.name << endl;
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // 关闭搜索句柄
}

void ResourceContent::initialize(SDL_Renderer* sdlRenderer, const char* path)
{
	m_sdlRenderer = sdlRenderer;
	loadResources(path);
}