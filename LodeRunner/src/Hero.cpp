#include "..\include\Hero.h"

Hero::Hero(const sf::Vector2f& position) : Unit(position)
{
	animations[int(AnimationIndex::Climb)] = AnimateUnit(0, Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingLeft)] = AnimateUnit(0, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::WalkingRight)] = AnimateUnit(8 * Constants::Unit_Size, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::Falling)] = AnimateUnit(4 * Constants::Unit_Size, 0, Constants::Unit_Size, Constants::Unit_Size);
	animations[int(AnimationIndex::Disintegrate)] = AnimateUnit(0, 4 * Constants::Unit_Size, Constants::Unit_Size, Constants::Unit_Size);
	//climb rope to do

}

std::unique_ptr<Unit> Hero::clone() 
{
	return std::make_unique<Hero>(*this);
}

void Hero::Disintegrate() 
{
	curAnimation = AnimationIndex::Disintegrate;
}