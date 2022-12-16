#pragma once
#include "Hero.h"
#include "Enemy.h"
enum UnitType
{
	HERO,
	ENEMY
};

class UnitFactory
{
private:
	std::unordered_map<UnitType, std::unique_ptr<Unit>, std::hash<int> > m_Units;
public:
	UnitFactory(const sf::Vector2f& position = sf::Vector2f(0.0f,0.0f))
	{
		m_Units[HERO] = std::make_unique<Hero>(position);
		m_Units[ENEMY] = std::make_unique<Enemy>(position);
	}

	std::unique_ptr<Unit> createUnit(UnitType UnitType)
	{
		return m_Units[UnitType]->clone();
	}
};

