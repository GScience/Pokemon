
#include "ResourceContent.h"
#include "Application.h"
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <io.h>

using namespace std;

void ResourceContent::loadResources(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(((string)dir + "\\*.*").c_str(), &findData);
	if (handle == -1)        // ����Ƿ�ɹ�
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

			if (extensionName == ".png" || extensionName == ".jpg" || extensionName == ".gif" || extensionName == ".bmp")
				add<SDL_Texture>(IMG_LoadTexture(application.getRenderer(), fileName.c_str()), fileName.c_str());

			cout << "Load file " << findData.name << endl;
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // �ر��������
}

void ResourceContent::initialize()
{
	loadResources(m_path);
}