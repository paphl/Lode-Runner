#pragma once
#include "Unit.h"

class Enemy : public Unit
{
public:
	Enemy(const sf::Vector2f& position);
	std::unique_ptr<Unit> clone() override;
	void Disintegrate() override  {};
private:

};

