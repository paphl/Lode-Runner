#include "..\include\Enemy.h"


Enemy::Enemy(const sf::Vector2f& position) : Unit(position)
{
	animations[int(AnimationIndex::Climb)] = AnimateUnit(0, 4*Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingLeft)] = AnimateUnit(0, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingRight)] = AnimateUnit(8 * Constants::Unit_Size, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::Falling)] = AnimateUnit(4 * Constants::Unit_Size, 3 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
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