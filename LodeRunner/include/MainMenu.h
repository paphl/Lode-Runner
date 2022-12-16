#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "State.h"
#include "Game.h"
#include "FilePaths.h"
#include "LvlSelectionMenu.h"
using namespace std;
using namespace sf;

class MainMenuState :public State
{
public:
	MainMenuState(GameDataRef ref);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void MoveUp();
	void MoveDown();
	int MainMenuPressed() {
		return MainMenuSelected;
	}

private:
	GameDataRef _data;
	sf::RectangleShape  _background;

	int MainMenuSelected;
	Font font; // font of the menu text
	Text mainMenu[Max_main_menu];
	sf::RectangleShape menuSelector; //displays block over the selected option from the menu
	sf::Texture menuSelectorTexture; //texture for the menuSelector
};