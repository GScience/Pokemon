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
	template <class Type> void add(Type* type, const char* key)
	{
		m_resourceMap[key] = type;
	}

	//get resource
	template <class Type> Type* get(const char* resourcePath)
	{
		return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath));
	}
};