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
	SDL_Renderer*	m_renderer;

	//res content
	ResourceContent m_resContent = ResourceContent("Resources");

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

	//get renderer
	SDL_Renderer* getRenderer() { return m_renderer; }

	//change scene
	void switchScene(const char* sceneName)
	{
		m_nowScene = sceneMap.at(sceneName);
	}

	//keyboard event(key,action)
	Event<int, keyAction> keyEvent;

	//run the program
	void run();

	//add scene
	template <class Scene> void addScene(const char* sceneName)
	{
		sceneMap[sceneName] = reinterpret_cast<SceneBase*>(new Scene());

		if (m_nowScene == nullptr && sceneMap.size() == 1)
			m_nowScene = sceneMap[sceneName];
	}
};

#define application Application::getInstance()