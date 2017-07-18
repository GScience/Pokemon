#pragma once

#include "ResourceContent.h"
#include "Event.h"
#include "SceneBase.h"
#include "Texture.h"
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <functional>

enum keyAction { keyDown, keyUp };

class Application
{
private:
	//program title
	const char*		m_title;

	//SDL
	SDL_Window*		m_sdlWindow;
	SDL_Renderer*	m_sdlRenderer;

	//res content
	ResourceContent m_resContent = ResourceContent();

	//scene list
	std::map<std::string, std::shared_ptr<SceneBase>> sceneMap;

	//now scene
	std::shared_ptr<SceneBase> m_nowScene = nullptr;

	Application() {}

	//run the program
	void run();
public:
	//get instance
	static Application& getInstance()
	{
		static Application app;
		return app;
	}

	//get resource content
	ResourceContent& getResourceContent() { return m_resContent; }

	//change scene
	void switchScene(const char* sceneName)
	{
		m_nowScene = sceneMap.at(sceneName);
	}

	/*Event start*/

	//keyboard event(key,action)
	Event<int, keyAction> keyEvent;

	//init event(call when application init)
	Event<> initEvent;

	/*Event end*/

	//start the program
	void start();

	//add scene
	template <class Scene> void addScene(const char* sceneName)
	{
		auto newScene = std::make_shared<Scene>(m_sdlRenderer);
		sceneMap[sceneName] = newScene;

		if (m_nowScene == nullptr && sceneMap.size() == 1)
			m_nowScene = newScene;
	}

	Texture* getTexture(const char* name)
	{
		return m_resContent.get<Texture>(name);
	}
};

#define application Application::getInstance()