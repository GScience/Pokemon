#pragma once

#include <SDL.h>
#include <map>
#include <string>

class ResourceContent
{
private:
	SDL_Renderer*					m_sdlRenderer;
	std::map<std::string, void*>	m_resourceMap;

	//load all resources
	void loadResources(const char * dir);

public:
	//init
	void initialize(SDL_Renderer* sdlRenderer, const char* path);

	//add
	void add(void* type, const char* resourcePath)
	{
		m_resourceMap[resourcePath] = type;
	}

	//get resource
	template <class Type> Type* get(const char* resourcePath)
	{
		return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath));
	}

	//try to get resource
	template <class Type> Type* tryGet(const char* resourcePath)
	{
		try
		{
			return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath));
		}
		catch (std::exception)
		{
			return nullptr;
		}
	}
};