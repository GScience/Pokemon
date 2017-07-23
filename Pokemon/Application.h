#pragma once

#include "ResourceContent.h"
#include "Event.h"
#include "SceneBase.h"
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <functional>

enum KeyAction { keyDown, keyUp };

class Texture;
class GameModeBase;

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

	//controller
	std::shared_ptr<GameModeBase> m_gameMode;

	//nowTime
	uint32_t m_nowTime;

	//keyboard state
	const uint8_t* m_keyStates = SDL_GetKeyboardState(nullptr);

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
	
	//check whether key has been pressed
	uint8_t getKeyState(unsigned int keyCode) { return m_keyStates[keyCode]; }

	//get resource content
	ResourceContent& getResourceContent() { return m_resContent; }

	//change scene
	void switchScene(const char* sceneName) 
	{
		m_gameMode = nullptr;
		m_nowScene	 = sceneMap.at(sceneName);

		m_nowScene->initialize();
	}

	//get time
	uint32_t getTime() const { return m_nowTime; }

	/*Event start*/

	//keyboard event(key,action)
	Event<int, KeyAction>	keyEvent;
	//tick event
	Event<double>			tickEvent;
	//init event(call when application init)
	Event<> initEvent;

	/*Event end*/

	//start the program
	void start();

	//bind controller
	template <class GameMode> void setGameMode()
	{
		m_gameMode = std::make_shared<GameMode>(m_nowScene);
	}

	//add scene
	template <class Scene> void addScene(const char* sceneName)
	{
		auto newScene = std::make_shared<Scene>(m_sdlRenderer);
		sceneMap[sceneName] = newScene;
	}
};

#define application Application::getInstance()