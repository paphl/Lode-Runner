#include "..\include\Enemy.h"


Enemy::Enemy(const sf::Vector2f& position) : Unit(position)
{
	animations[int(AnimationIndex::Climb)] = AnimateUnit(0, 4*Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingLeft)] = AnimateUnit(0, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingRight)] = AnimateUnit(8 * Constants::Unit_Size, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::Falling)] = AnimateUnit(4 * Constants::Unit_Size, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);

	animations[int(AnimationIndex::RopeLeft)] = AnimateUnit(4 * Constants::Unit_Size, 4*Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::RopeRight)] = AnimateUnit(4 * Constants::Unit_Size, 8 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	//climb rope to do
}

std::unique_ptr<Unit> Enemy::clone()
{
	return std::make_unique<Enemy>(*this);
}

void Enemy::pickUpGold(std::vector<Tile*>& tiles)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->getTileType() == "Gold" && this->isColliding(tiles[i]->getGlobalBounds()) && goldCounter < 1 && tiles[i]->getIsVisible())
		{
			goldCounter++;
			tiles[i]->setIsVisible(false);
			//hide the gold sprite
			//gold sprite drops when trapped by unit and is put on top of the enemy
		}
	}
}

void Enemy::choosePath(std::vector<Tile*>& tiles)
{
	sf::Time delay = sf::seconds(1.0f);
	dir = sf::Vector2f(0, 0);

	if (clock.getElapsedTime().asSeconds() >  delay.asSeconds() )
	{
		clock.restart();
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i]->getTileType() == "Rope" && this->isColliding(tiles[i]->getGlobalBounds()))
			{
				this->setOnRope(true);
				direction = rand() % 3;
				break;
			}
			else if (tiles[i]->getTileType() == "Ladder" && this->isColliding(tiles[i]->getGlobalBounds()))
			{
				direction = rand() % 4;
				break;
			}
			else
			{
				direction = rand() % 2;
			}
		}
		
	}

		
	if (this->getIsFalling())
	{
		if (!this->GravityPull(tiles) && !this->getOnRope())
		{
			dir = sf::Vector2f(0, 0);
			dir.y += 1.0f;
			this->SetDirection(dir);
			this->setIsFalling(true);
			return;
		}
		else
		{
			dir.y += 0.0f;
			this->setIsFalling(false);
		}
	}
		if (direction == 0) //left
		{
			dir.x -= 1;
			std::vector<Tile*>::iterator ptrTiles;

			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if (this->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getIsBlocking())
					{
					if (this->getGlobalBounds().left <= (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width &&
						this->getGlobalBounds().left + this->getGlobalBounds().width >= (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width
						) //check if hero enter
					{
						if ((this->getGlobalBounds().top > (*ptrTiles)->getGlobalBounds().top &&
							this->getGlobalBounds().top < (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height) ||
							(this->getGlobalBounds().top + this->getGlobalBounds().height - 3.0f > (*ptrTiles)->getGlobalBounds().top &&
								this->getGlobalBounds().top + this->getGlobalBounds().height <= (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height))
						{
							dir.x = 0.0f;
							return;
						}
					}
				}
			}
		} 
		else if (direction == 1) //right
		{
			dir.x += 1;
			std::vector<Tile*>::iterator ptrTiles;

			float heroLeftBound = this->getGlobalBounds().left + this->getGlobalBounds().width + 2.5f;

			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if (this->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getIsBlocking())
				{
					if (this->getGlobalBounds().left >= (*ptrTiles)->getGlobalBounds().left - (*ptrTiles)->getGlobalBounds().width &&
						this->getGlobalBounds().left - this->getGlobalBounds().width < (*ptrTiles)->getGlobalBounds().left + (*ptrTiles)->getGlobalBounds().width) //check if hero enter
						if ((this->getGlobalBounds().top > (*ptrTiles)->getGlobalBounds().top &&
							this->getGlobalBounds().top < (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height) ||
							(this->getGlobalBounds().top + this->getGlobalBounds().height - 3.0f > (*ptrTiles)->getGlobalBounds().top &&
								this->getGlobalBounds().top + this->getGlobalBounds().height <= (*ptrTiles)->getGlobalBounds().top + (*ptrTiles)->getGlobalBounds().height))
						{
							dir.x = 0.0f;
							return;
						}
				}

				if (this->isColliding((*ptrTiles)->getGlobalBounds()) && (*ptrTiles)->getTileType() == "Rope")
				{
					this->setOnRope(true);
					break;
				}

				if (this->getOnRope()) {
					this->setOnRope(false);
				}
			}
		}
		else if (direction == 2) //down 
		{
			std::vector<Tile*>::iterator ptrTiles;
			for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
			{
				if ((*ptrTiles)->getTileType() == "Ladder")
			{
				if (this->isColliding((*ptrTiles)->getGlobalBounds()) && this->getPosition().x > (*ptrTiles)->getPosition().x - 36.0f &&
					this->getPosition().x < (*ptrTiles)->getPosition().x + 36.0f)
				{
					std::vector<Tile*>::iterator itrTiles;
					for (itrTiles = tiles.begin(); itrTiles < tiles.end(); itrTiles++) //checks when going down if collides with an other object that has collision
					{
						if ((*itrTiles)->getIsBlocking() &&
							this->getGlobalBounds().top + this->getGlobalBounds().height + 3.0f > (*itrTiles)->getGlobalBounds().top &&
							this->getGlobalBounds().top < (*itrTiles)->getGlobalBounds().top &&
							this->getPosition().x >(*itrTiles)->getPosition().x - 36.0f &&
							this->getPosition().x < (*itrTiles)->getPosition().x + 36.0f)
						{
							dir.y = 0;
							return;
						}
					}

					if ((int)this->getPosition().y - 2 == (*ptrTiles)->getPosition().y + Constants::SIZE_OF_TILE)
					{
						dir.y = 0;
						return;
					}

					dir.y += 1.0f;
					this->setPos((*ptrTiles)->getPosition().x, this->getPosition().y);
					this->SetDirection(dir);
					return;
				}
			}
			if ((*ptrTiles)->getTileType() == "Rope" && this->isColliding((*ptrTiles)->getGlobalBounds()))
			{
				this->setOnRope(false);
			}
		}
	}
		else if (direction == 3) //up
	{
		std::vector<Tile*>::iterator ptrTiles;
		for (ptrTiles = tiles.begin(); ptrTiles < tiles.end(); ptrTiles++)
		{
			if ((*ptrTiles)->getTileType() == "Ladder")
			{
				if (this->isColliding((*ptrTiles)->getGlobalBounds()) && this->getPosition().x > (*ptrTiles)->getPosition().x - 36.0f &&
					this->getPosition().x < (*ptrTiles)->getPosition().x + 36.0f)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						if ((int)this->getPosition().y + 2 == (*ptrTiles)->getPosition().y - Constants::SIZE_OF_TILE)
						{
							dir.y = 0;
							return;
						}
						dir.y -= 1.0f;
					}

				}
			}
		}

	}
		this->SetDirection(dir);

		if (!this->GravityPull(tiles) && !this->getOnRope())
		{
			//dir = sf::Vector2f(0, 0);
			dir.y += 1.0f;
			this->SetDirection(dir);
			this->setIsFalling(true);
			return;
		}
		else
		{
			dir.y += 0.0f;
			this->setIsFalling(false);
		}
}
