#include "..\include\Map.h"

Map::Map(GameDataRef data) : _data(data)
{

}

void Map::Init()
{
	file_.open(this->_data->path_level);
	if(!file_.is_open())
	{
		std::cout << "Error loading file" << std::endl;
		return;
	}
	std::string sLine;
	while (std::getline(file_, sLine))
	{
		vRow.push_back(sLine);
	}
	file_.close();

	loadMap();
	view.setSize(950, 800);

}

Map::~Map()
{
    //dtor
}

void Map::loadMap()
{
	std::vector<std::string>::iterator ptr;
	float posY = 0.0f;
	float posX = 0.0f;
	Tile* tile;
	for (ptr = vRow.begin(); ptr < vRow.end(); ptr++)
	{
		for (int i = 0; i < ptr->size(); i++)
		{
			switch ((*ptr)[i])
			{
			case '+':
				hero = unitFactory.createUnit(UnitType::HERO);
				hero->setPosition(sf::Vector2f(posX, posY));
				view.setCenter(units.back()->getPosition()); //set starting pos of the view equal to hero
				break;
			case '-':
				units.push_back(unitFactory.createUnit(UnitType::ENEMY));
				units.back()->setPosition(sf::Vector2f(posX, posY));
				break;
			case 'H':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::LADDER, posX, posY));
				break;
			case 'h':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::LADDER, posX, posY));
				break;
			case '$':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::GOLD, posX, posY));
				break;
			case '~':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::ROPE, posX, posY));
				break;
			case 'X':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::DIRT, posX, posY));
				break;
			default:
				break;
			}
			posX += Constants::SIZE_OF_TILE;
		}
		if (posX > mapSize.x)
		{
			mapSize.x = posX;
		}
		posX = 0.0f;
		posY += Constants::SIZE_OF_TILE;
	}
	mapSize.y = posY;
}

void Map::Draw(float dt)
{

	this->_data->window.clear();


	std::vector<std::unique_ptr<Unit>>::iterator ptrUnits;
	for (ptrUnits = units.begin(); ptrUnits < units.end(); ptrUnits++)
	{
		(*ptrUnits)->Draw(this->_data->window);
	}

	std::vector<Tile*>::iterator ptrTiles;
	for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
	{
		(*ptrTiles)->Draw(this->_data->window);
	}

	hero->Draw(this->_data->window);

	this->_data->window.display();
}

void Map::HandleInput()
{
	sf::Event event;
	float heroLeftBound; //used for left and right collision check

	while (this->_data->window.pollEvent(event))
	{	
		if (hero->getIsFalling())
		{
			return;
		}
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		sf::Vector2f dir = { 0.0f, 0.0f }; // used to move hero

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//to be tested
			std::vector<Tile*>::iterator ptrTiles;
			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if ((*ptrTiles)->getTileType() == "Ladder")
				{
					if (hero->isColliding((*ptrTiles)->getGlobalBounds()) && hero->getPosition().x  > (*ptrTiles)->getPosition().x - 6.0f && hero->getPosition().x < (*ptrTiles)->getPosition().x + 6.0f)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							float temp = hero->getPosition().y;
							float temp1 = (*ptrTiles)->getPosition().y - Constants::SIZE_OF_TILE;
							if ((int)hero->getPosition().y + 2 == (*ptrTiles)->getPosition().y - Constants::SIZE_OF_TILE)
							{
								return;
							}
							dir.y -= 2.0f;
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							if ((int)hero->getPosition().y - 2 == (*ptrTiles)->getPosition().y + Constants::SIZE_OF_TILE)
							{
								return;
							}
							dir.y += 2.0f;
						}
					}
				}
				
			}
			
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			std::vector<Tile*>::iterator ptrTiles;
			dir.x -= 3.0f;

			for ( ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{	
				if (hero->isColliding((*ptrTiles)->getGlobalBounds())  && (*ptrTiles)->getIsBlocking())
				{
					if (hero->getGlobalBounds().left  <= (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width &&
						hero->getGlobalBounds().left + hero->getGlobalBounds().width >= (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width
						) //check if hero enter
					{
						if ((hero->getGlobalBounds().top > (*ptrTiles)->getGlobalBounds().top &&
							hero->getGlobalBounds().top < (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height) ||
							(hero->getGlobalBounds().top + hero->getGlobalBounds().height -3.0f > (*ptrTiles)->getGlobalBounds().top &&
							hero->getGlobalBounds().top + hero->getGlobalBounds().height <= (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height))
						{
							dir.x = 0.0f;
						}
					}
				}
				
					
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::vector<Tile*>::iterator ptrTiles;
			dir.x += 3.0f;
			float heroLeftBound = hero->getGlobalBounds().left + hero->getGlobalBounds().width + 2.5f;

			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if (hero->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getIsBlocking())
				{
					if (hero->getGlobalBounds().left  >= (*ptrTiles)->getGlobalBounds().left - (*ptrTiles)->getGlobalBounds().width &&
						hero->getGlobalBounds().left - hero->getGlobalBounds().width < (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width) //check if hero enter
						if ((hero->getGlobalBounds().top > (*ptrTiles)->getGlobalBounds().top &&
							hero->getGlobalBounds().top < (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height) ||
							(hero->getGlobalBounds().top + hero->getGlobalBounds().height - 3.0f > (*ptrTiles)->getGlobalBounds().top &&
							hero->getGlobalBounds().top + hero->getGlobalBounds().height  <= (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height))
						{
							dir.x = 0.0f;
						}
				}
			}
		}
		
		hero->SetDirection(dir);
	}



}

void Map::Update(float dt)
{


	sf::Vector2f dirs = { 0.0f, 0.0f };
	std::vector<std::unique_ptr<Unit>>::iterator ptrUnits;
	for (ptrUnits = units.begin(); ptrUnits < units.end(); ptrUnits++)
	{
		(*ptrUnits)->Update(dt);
		if (!(*ptrUnits)->GravityPull(tiles))
		{
			dirs.y += 1.0f;
			(*ptrUnits)->SetDirection(dirs);
			(*ptrUnits)->setIsFalling(true);
		}
		else
		{
			dirs.y += 0.0f;
			(*ptrUnits)->SetDirection(dirs);
			(*ptrUnits)->setIsFalling(false);
		}
	}
	hero->Update(dt); //update before unit before gravity takes effect
	//simulates falling if obj isnt collinding with any tile
	sf::Vector2f dir = { 0.0f, 0.0f };
	if (!hero->GravityPull(tiles))
	{
		dir.y += 1.0f;
		hero->SetDirection(dir);
		hero->setIsFalling(true);
	}
	else
	{
		dir.y += 0.0f;
		hero->SetDirection(dir);
		hero->setIsFalling(false);
	}

	UpdateView(dt); //always after updating the hero

	//end of hero falling 


}

void Map::UpdateView(float dt)
{
	sf::Vector2f dir = { 0.0f, 0.0f }; // used to move view



	//checks for left movement
	if (hero->getPosition().x < view.getCenter().x - (view.getSize().x / 4.0f)  ) //checks ifhero is out of desired bound move camera only if camera most left corner is not 0
	{
		dir.x -= 2.5f;
	}
	//checks for right movement
	else if (hero->getPosition().x > view.getCenter().x + (view.getSize().x / 4.0f)) //checks ifhero is out of desired bound move camera only if camera most left corner is not 0
	{
		dir.x += 2.5f;
	}

	sf::Vector2f vel = dir * 100.0f;
	view.move(vel * dt);

	if (view.getCenter().x - (view.getSize().x / 2) < 0)
	{
		return;
	}

	if (view.getCenter().x + (view.getSize().x / 2) > mapSize.x)
	{
		return;
	}

	this->_data->window.setView(view);
}