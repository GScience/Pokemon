#pragma once

#include <functional>
#include <memory>
#include <SDL.h>
#include <map>
#include <string>

class ResourceContent
{
private:
	SDL_Renderer*	m_sdlRenderer;
	std::map <std::string, std::unique_ptr<void, std::function<void(void*)>>>	m_resourceMap;

	//load all resources
	void loadResources(const char * dir);

public:
	//init
	void initialize(SDL_Renderer* sdlRenderer, const char* path);

	//add
	void add(const char* resourcePath, void* pointer)
	{
		m_resourceMap[resourcePath] = std::unique_ptr<void, std::function<void(void*)>>(pointer, [](void*) {});
	}
	template <class Type, class ...InitVar> void add(const char* resourcePath, InitVar... vars)
	{
		std::unique_ptr<Type> shader = std::make_unique<Type>(vars...);
		m_resourceMap[resourcePath] = std::unique_ptr<void, std::function<void(void*)>>(shader.get(), [](void*) {});
		shader.release();
	}

	//get resource
	template <class Type> Type* get(const char* resourcePath)
	{
		return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath).get());
	}

	//try to get resource
	template <class Type> Type* tryGet(const char* resourcePath)
	{
		try
		{
			return get<Type>(resourcePath);
		}
		catch (std::exception)
		{
			return nullptr;
		}
	}
};