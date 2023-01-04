#include "..\include\LvlSelectionMenu.h"

//constructor
LvlSlectionMenuState::LvlSlectionMenuState(GameDataRef data) : _data(data)
{

}

//on initialize
void LvlSlectionMenuState::Init()
{
	//try loading font
	if (!font.loadFromFile("assets/Fonts/AlexandriaFLF.ttf"))
	{
		std::cout << "No font found";
	}

	btnTexture = this->_data->resources.Acquire(Texture_Paths::Buttons);
	buttons[0] = { 160, 300, 420, 190 };
	buttons[1] = { 600, 300, 410, 190 };

	for (const auto & entry : std::experimental::filesystem::directory_iterator(Other_Directories::Level_Directory)) // not  in experimental since c++17 onwards
	{
		//setting text name and styling to the lvl button
		allLvlCount++;
		std::string name = "Level " + std::to_string(allLvlCount);
		btnText.push_back(std::unique_ptr<sf::Text>(new sf::Text(name, font, MENU_Size)));
		allLevelPaths.push_back(entry.path().generic_string());
		//setting up the sprites for the button visu
		btnSprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*btnTexture, buttons[0])));
		btnSprites.back()->setScale(0.6f, 0.6f);

	}
	this->_data->allLevels = allLevelPaths;
	(*btnSprites[0]).setTextureRect(buttons[1]); //set hightlight the first lvl on initialize
	
	int i = 0;
	float pos_y = Constants::POSITION_75;
	for (int i = 0; i < allLvlCount; ++i) {
		if (i % 2 != 0)
		{
			btnSprites[i]->setPosition(sf::Vector2f(Constants::POSITION_450, pos_y));
			btnText[i]->setPosition(sf::Vector2f(Constants::POSITION_450 + 20, pos_y));
		}
		else {
			pos_y += Constants::POSITION_75*2; // every non even number level to display push it down example lvl 1 and lvl 2 will be in the same row lvl 3 and lvl 4 will be on a next one
			btnSprites[i]->setPosition(sf::Vector2f(Constants::POSITION_75, pos_y));
			btnText[i]->setPosition(sf::Vector2f(Constants::POSITION_75 + 20, pos_y));
		}
	}
}

//event are handled here for Lvl Selector Menu
void LvlSlectionMenuState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				this->MoveUp();
				break;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				this->MoveDown();
				break;
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				this->MoveLeft();
				break;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				this->MoveRight();
				break;
			}
			if (event.key.code = sf::Keyboard::Enter)
			{
				this->_data->path_level = allLevelPaths[lvlSelected];
				this->_data->machine.AddState(StateRef(new Map(_data)), true);
			}
		}
	}
}

void LvlSlectionMenuState::MoveUp()
{
	if (lvlSelected - 2 >= -2)
	{
		(*btnSprites[lvlSelected]).setTextureRect(buttons[0]);
		lvlSelected -= 2;
		if (lvlSelected  < 0)
		{
			lvlSelected = allLvlCount + lvlSelected;
			if (lvlSelected % 2 != 0)
			{
				lvlSelected++;
			}
		}
		(*btnSprites[lvlSelected]).setTextureRect(buttons[1]);
	}
}

void LvlSlectionMenuState::MoveDown()
{
	if (lvlSelected + 2 <= allLvlCount + 2)
	{
		(*btnSprites[lvlSelected]).setTextureRect(buttons[0]);
		lvlSelected += 2;
		if (lvlSelected >= allLvlCount)
		{
			lvlSelected = lvlSelected - allLvlCount;
			if (lvlSelected % 2 != 0)
			{
				lvlSelected--;
			}
		}
		(*btnSprites[lvlSelected]).setTextureRect(buttons[1]);
	}
}

void LvlSlectionMenuState::MoveLeft()
{
	(*btnSprites[lvlSelected]).setTextureRect(buttons[0]);
	lvlSelected--;
	if (lvlSelected < 0)
	{
		lvlSelected = allLvlCount - 1;
	}

	(*btnSprites[lvlSelected]).setTextureRect(buttons[1]);
}

void LvlSlectionMenuState::MoveRight()
{
	(*btnSprites[lvlSelected]).setTextureRect(buttons[0]);
	lvlSelected++;
	if (lvlSelected == allLvlCount)
	{
		lvlSelected = 0;
	}

	(*btnSprites[lvlSelected]).setTextureRect(buttons[1]);
}

void LvlSlectionMenuState::Update(float dt)
{

}

void LvlSlectionMenuState::Draw(float dt)
{
	this->_data->window.clear();
	for (int i = 0; i < allLvlCount; i++)
	{
		this->_data->window.draw((*btnSprites[i]));
		this->_data->window.draw((*btnText[i]));
	}

	this->_data->window.display();
}

