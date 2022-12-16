#pragma once
#include <SFML/Graphics.hpp>
#include "include/MainMenu.h"
#include "include/FilePaths.h"
#include "include/Game.h"


//this is used the game to be displayed better after a resizing
void ResizeView(const sf::RenderTarget& rt, sf::View& view)
{
	float aspectRatio = float(rt.getSize().x) / float(rt.getSize().y);
	view.setSize(Constants::VIEW_HEIGHT*aspectRatio, Constants::VIEW_HEIGHT);
}
int main()
{
	Game::Game(Constants::VIEW_HEIGHT, Constants::VIEW_HEIGHT, "Lode Runner");
    return 0;
}
