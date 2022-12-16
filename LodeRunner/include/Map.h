#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "FilePaths.h"
#include "UnitFactory.h"
#include "Game.h"
#include "../src/TileFactory.cpp"
#include "State.h"

class Map : public State
{
    public:
		Map(GameDataRef ref);
		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void UpdateView(float dt);
        virtual ~Map();
		void loadMap();

    private:
		UnitFactory unitFactory;
		std::vector<std::unique_ptr<Unit>> units;
		std::vector<Tile*> tiles;
		GameDataRef _data;
		std::vector<std::string> vRow;
		sf::View view;
		std::unique_ptr<Unit> hero;
		std::ifstream file_;
		sf::Vector2f mapSize = { 0.0f, 0.0f }; //needed for camera moovement
};

