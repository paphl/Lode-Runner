#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "ResourceHolder.h"


	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		ResourceHolder resources;
		std::string path_level;
		std::vector<std::string> allLevels;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);
	private:
		const float dt = 1.0f / 60.0f; //framerate
		sf::Clock _clock;
		GameDataRef _data = std::make_shared<GameData>();

		void Run();

	};


