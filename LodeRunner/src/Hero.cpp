#include "..\include\Hero.h"

Hero::Hero(const sf::Vector2f& position) : Unit(position)
{
	animations[int(AnimationIndex::Climb)] = AnimateUnit(0, Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingLeft)] = AnimateUnit(0, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingRight)] = AnimateUnit(8 * Constants::Unit_Size, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::Falling)] = AnimateUnit(4 * Constants::Unit_Size, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::DisintegrateLeft)] = AnimateUnit(0, 2 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::DisintegrateRight)] = AnimateUnit(8 * Constants::Unit_Size, 2 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);

	animations[int(AnimationIndex::RopeLeft)] = AnimateUnit(4 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::RopeRight)] = AnimateUnit(4 * Constants::Unit_Size, 2*Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);

	//climb rope to do

}

std::unique_ptr<Unit> Hero::clone() 
{
	return std::make_unique<Hero>(*this);
}

void Hero::Disintegrate(Constants::DIG_DIRECTION dir)
{
	if (dir == Constants::DIG_DIRECTION::LEFT)
	{
		curAnimation = AnimationIndex::DisintegrateLeft;

	}
	else
	{
		curAnimation = AnimationIndex::DisintegrateRight;

	}
}

void Hero::pickUpGold(std::vector<Tile*>& tiles)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->getTileType() == "Gold" && this->isColliding(tiles[i]->getGlobalBounds()) && tiles[i]->getIsVisible())
		{
			goldCounter++;
			tiles[i]->setIsVisible(false);
			//hide the gold sprite
			//gold sprite drops when trapped by unit and is put on top of the enemy
		}
	}
}