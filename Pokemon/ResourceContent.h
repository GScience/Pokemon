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
	std::map <std::string, std::unique_ptr<void, std::function<void(void*)>>> m_resourceMap;

	//load all resources
	void initResources(const char * dir);

	//load res
	void* loadResource(const char* fileName);

public:
	//init
	void initialize(SDL_Renderer* sdlRenderer, const char* path);

	//add
	void add(const char* resourcePath, void* pointer)
	{
		m_resourceMap[resourcePath] = std::unique_ptr<void, std::function<void(void*)>>(pointer, [](void*) {});
	}
	template <class Type, class ...InitVar> Type* add(const char* resourcePath, InitVar... vars)
	{
		std::unique_ptr<Type> uniquePtr = std::make_unique<Type>(vars...);
		Type* pointer = uniquePtr.get();
		m_resourceMap[resourcePath] = std::unique_ptr<void, std::function<void(void*)>>(pointer, [](void*) {});
		uniquePtr.release();
		return pointer;
	}

	//get resource(if res doesn't exist will be load)
	template <class Type> Type* get(const char* resourcePath)
	{
		try
		{
			return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath).get());
		}
		catch (std::exception)
		{
			return reinterpret_cast<Type*>(loadResource(resourcePath));
		}
	}

	//get resource(if res doesn't exist will return nullptr
	template <class Type> Type* tryGet(const char* resourcePath)
	{
		try
		{
			return reinterpret_cast<Type*>(m_resourceMap.at(resourcePath).get());
		}
		catch (std::exception)
		{
			return nullptr;
		}
	}

	//get texture
	template <class Type = Texture> Type* getTexture(const char* resourcePath)
	{
		return get<Type>(resourcePath);
	}
};