#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "State.h"
#include "Game.h"
#include "Map.h"
#include "FilePaths.h"

class LvlSlectionMenuState :public State
{
public:
	LvlSlectionMenuState(GameDataRef ref);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	int LvlSelected() {
		return lvlSelected;
	}

private:
	GameDataRef _data;

	int allLvlCount = 0; //total summ of lvls
	int lvlSelected = 0; //current selected lvl
	sf::Font font; 
	std::vector<std::string> allLevelPaths;
	std::vector<std::unique_ptr<sf::Text>> btnText;
	std::vector<std::unique_ptr<sf::Sprite>> btnSprites;
	std::shared_ptr<sf::Texture> btnTexture;
	sf::IntRect buttons[2];
};