#include "..\include\SplashState.h"
#include <sstream>
#include <iostream>
#include "..\include\MainMenu.h"

SplashState::SplashState(GameDataRef data) : _data(data)
{
}

void SplashState::Init()
{
	std::shared_ptr<sf::Texture> pTexture  =  this->_data->resources.Acquire(Texture_Paths::My_Logo);
	
	_background.setTexture(*pTexture);
	_background.setScale(0.25f, 0.17f);
}

void SplashState::HandleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}
void SplashState::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > Constants::Splash_State_Show_Time)
	{
		this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
	}
}
void SplashState::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}