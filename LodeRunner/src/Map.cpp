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
				tiles.back()->setIsVisible(false);
				ladderToNextLevel.push_back(tiles.back());
				break;
			case '$':
				tiles.push_back(TileFactory::createTile(TILE_TYPE::GOLD, posX, posY));
				goldCounter++;
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

	std::vector<Tile*>::iterator ptrTiles;
	for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
	{
		if((*ptrTiles)->getIsVisible()) // draw the tile when isVisible is true 
			(*ptrTiles)->Draw(this->_data->window);
	}

	std::vector<std::unique_ptr<Unit>>::iterator ptrUnits;
	for (ptrUnits = units.begin(); ptrUnits < units.end(); ptrUnits++)
	{
		(*ptrUnits)->Draw(this->_data->window);
	}

	hero->Draw(this->_data->window);

	this->_data->window.display();
}

void Map::HandleInput()
{
	sf::Event event;
	float heroLeftBound; //used for left and right collision check

	if (hero->getIsFalling())
	{
		return;
	}

	while (this->_data->window.pollEvent(event))
	{	
	
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		sf::Vector2f dir = { 0.0f, 0.0f }; // used to move hero
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			std::vector<Tile*>::iterator ptrTiles;
			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if ((*ptrTiles)->getTileType() == "Ladder")
				{
					if (hero->isColliding((*ptrTiles)->getGlobalBounds()) && hero->getPosition().x > (*ptrTiles)->getPosition().x - 36.0f &&
						hero->getPosition().x < (*ptrTiles)->getPosition().x + 36.0f)
					{
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						{
							if ((int)hero->getPosition().y + 2 == (*ptrTiles)->getPosition().y - Constants::SIZE_OF_TILE)
							{
								return;
							}
							dir.y -= 2.0f;
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						{
							std::vector<Tile*>::iterator itrTiles;
							for (itrTiles = tiles.begin(); itrTiles < tiles.end(); itrTiles++) //checks when going down if collides with an other object that has collision
							{
								if ((*itrTiles)->getIsBlocking() && 
									hero->getGlobalBounds().top + hero->getGlobalBounds().height + 3.0f > (*itrTiles)->getGlobalBounds().top &&
									hero->getGlobalBounds().top < (*itrTiles)->getGlobalBounds().top &&
									hero->getPosition().x >(*itrTiles)->getPosition().x - 36.0f &&
									hero->getPosition().x < (*itrTiles)->getPosition().x + 36.0f)
								{
									return;
								}
							}

							if ((int)hero->getPosition().y - 2 == (*ptrTiles)->getPosition().y + Constants::SIZE_OF_TILE)
							{
								return;
							}

							dir.y += 2.0f;
						}
						hero->setPos((*ptrTiles)->getPosition().x, hero->getPosition().y);
						hero->SetDirection(dir);
						return;
					}
				}
				if ((*ptrTiles)->getTileType() == "Rope" && hero->isColliding((*ptrTiles)->getGlobalBounds()))
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						hero->setOnRope(false);
					}
			
				}
			}
			
		}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			std::vector<Tile*>::iterator ptrTiles;
			dir.x -= 2.0f;

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
				
				if (hero->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getTileType() == "Rope")
				{
					hero->setOnRope(true);
					break;
				}
				else if (hero->getOnRope()) {
					hero->setOnRope(false);
				}
			}

		}
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			std::vector<Tile*>::iterator ptrTiles;
			dir.x += 2.0f;
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

				if (hero->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getTileType() == "Rope")
				{
					hero->setOnRope(true);
					break;
				}
				else if(hero->getOnRope()) {
					hero->setOnRope(false);
				}
			}
		}
		
			hero->SetDirection(dir);
			isDigging = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				
				digDir = Constants::DIG_DIRECTION::LEFT;
				posX = hero->getGlobalBounds().left;
			}
			else
			{
				digDir = Constants::DIG_DIRECTION::RIGHT;
				posX = hero->getGlobalBounds().left + hero->getGlobalBounds().width;

			}
			isDigging = true;

		}

	}
}

void Map::Update(float dt)
{
	if (goldCounter == hero->getGoldCounter())
	{
		for (int i = 0; i < ladderToNextLevel.size(); i++)
		{
			ladderToNextLevel[i]->setIsVisible(true);
		}
	}

	sf::Vector2f dirs = { 0.0f, 0.0f };
	std::vector<std::unique_ptr<Unit>>::iterator ptrUnits;
	for (ptrUnits = units.begin(); ptrUnits < units.end(); ptrUnits++)
	{
		(*ptrUnits)->choosePath(tiles);
		(*ptrUnits)->Update(dt);

		(*ptrUnits)->pickUpGold(tiles); //checks if unit while moving picks up any gold
	}
	hero->Update(dt); //update before unit before gravity takes effect
	//simulates falling if obj isnt collinding with any tile
	sf::Vector2f dir = { 0.0f, 0.0f };
	if (!hero->GravityPull(tiles) && !hero->getOnRope())
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

	hero->pickUpGold(tiles);//hero if unit while moving picks up any gold

	UpdateView(dt); //always after updating the hero

	//end of hero falling 

	std::vector<Tile*>::iterator ptrTiles;
	for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
	{
		if ((*ptrTiles)->getIsVisible() && (*ptrTiles)->getTileType() == "Gold") // draw the tile when isVisible is true 
			(*ptrTiles)->Update(dt);

		if (isDigging)
		{
			if ((*ptrTiles)->getTileType() == "Dirt" && hero->getGlobalBounds().top + hero->getGlobalBounds().height / 2 < (*ptrTiles)->getGlobalBounds().top &&
				(*ptrTiles)->getGlobalBounds().top < hero->getGlobalBounds().top + hero->getGlobalBounds().height * 3 / 2)
			{
				//enter only if the tiles are exactly below the the hero unit x coord
				if (digDir == Constants::DIG_DIRECTION::LEFT && (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width / 2 < posX &&
					posX <= (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width + 10)
				{	
					//same as line 340 move to a method
					hero->Disintegrate(digDir);
					(*ptrTiles)->Update(dt);
					if ((*ptrTiles)->getFrame() == 10)
					{
						(*ptrTiles)->setIsVisible(false);
						diggedTiles.push_back((*ptrTiles));
						timerDiggedTiles.push_back(sf::Clock());

					}
					
				} else if(digDir == Constants::DIG_DIRECTION::RIGHT && (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width / 2 > posX &&
					posX >= (*ptrTiles)->getGlobalBounds().left - 10)
				{
					hero->Disintegrate(digDir);
					(*ptrTiles)->Update(dt);
					if ((*ptrTiles)->getFrame() == 10)
					{
						(*ptrTiles)->setIsVisible(false);
						diggedTiles.push_back((*ptrTiles));
						timerDiggedTiles.push_back(sf::Clock());

					}

				}
			}

		}
		else {
			if ((*ptrTiles)->getTileType() == "Dirt")
			{
				(*ptrTiles)->setFrame(0);
			}
		}
		
	}


	for (int i = 0; i < timerDiggedTiles.size(); i++)
	{
		if (timerDiggedTiles[i].getElapsedTime() > sf::seconds(5))
		{
			diggedTiles[i]->setIsVisible(true);
			diggedTiles[i]->setFrame(0);
			diggedTiles.erase(diggedTiles.begin() + i);
			timerDiggedTiles.erase(timerDiggedTiles.begin() + i);
			//
		}
	}
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

