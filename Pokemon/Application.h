#pragma once

#include "ResourceContent.h"
#include "Event.h"
#include "SceneBase.h"
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
	std::map<std::string, SceneBase*> sceneMap;

	//now scene
	SceneBase* m_nowScene = nullptr;

	Application() {}

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

	//run the program
	void run();

	//add scene
	template <class Scene> void addScene(const char* sceneName)
	{
		Scene* newScene = new Scene(m_sdlRenderer);
		sceneMap[sceneName] = reinterpret_cast<SceneBase*>(newScene);

		if (m_nowScene == nullptr && sceneMap.size() == 1)
			m_nowScene = reinterpret_cast<SceneBase*>(newScene);
	}
};

#define application Application::getInstance()