#include "..\include\MainMenu.h"


void MainMenuState::MoveUp()
{
    if(MainMenuSelected - 1 >= -1)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected--;
        menuSelector.move(0,-100);
        if(MainMenuSelected == -1)
        {
            MainMenuSelected = 2;
            menuSelector.move(0,300);
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

void MainMenuState::MoveDown()
{
    if(MainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
        menuSelector.move(0,100);
        if(MainMenuSelected == Max_main_menu )
        {
            MainMenuSelected = 0;
            menuSelector.move(0,-300);
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}



MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{

}

void MainMenuState::Init()
{
	_data->window.setSize(sf::Vector2u(Constants::WINDOW_SIZE_X_1200, Constants::WINDOW_SIZE_Y_800));
	_background.setSize(sf::Vector2f(Constants::WINDOW_SIZE_X_1200, Constants::WINDOW_SIZE_Y_800));
	_background.setTexture(&*this->_data->resources.Acquire(Texture_Paths::Menu_Background));
	_background.setScale(0.75f, 0.9f);

	//try loading font
	if (!font.loadFromFile("assets/Fonts/AlexandriaFLF.ttf"))
	{
		cout << "No font found";
	}



	//icon that is used for indication of the selected option
	menuSelector.setSize(Vector2f(MENU_Size, MENU_Size));
	menuSelector.setPosition(MENU_POS_X_Selector, MENU_POS_Y_Selector);
	menuSelector.setTexture(&*this->_data->resources.Acquire(Texture_Paths::Menu_Selector));

	//Play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Blue);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(MENU_Size);
	mainMenu[0].setPosition(MENU_POS_X, MENU_POS_Y_Play);
	//About
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Edit Mode");
	mainMenu[1].setCharacterSize(MENU_Size);
	mainMenu[1].setPosition(MENU_POS_X, MENU_POS_Y_About);
	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(MENU_Size);
	mainMenu[2].setPosition(MENU_POS_X, MENU_POS_Y_Exit);

	MainMenuSelected = 0;
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Up)
			{
				this->MoveUp();
				break;
			}
			if (event.key.code == Keyboard::Down)
			{
				this->MoveDown();
				break;
			}
			if (event.key.code = Keyboard::Enter)
			{
				if (MainMenuSelected == 0)
				{
					this->_data->machine.AddState(StateRef(new LvlSlectionMenuState(_data)), true);
				}
			}
		}
	}
}

void MainMenuState::Update(float dt)
{

}

void MainMenuState::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(_background);
	this->_data->window.draw(menuSelector);
	for (int i = 0; i < Max_main_menu; i++)
	{
		this->_data->window.draw(mainMenu[i]);
	}

	this->_data->window.display();
}