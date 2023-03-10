#ifndef HERO_H
#define HERO_H

#include "Unit.h"

class Hero : public Unit
{
    public:
		Hero(const sf::Vector2f& position);
		std::unique_ptr<Unit> clone() override;
		void Disintegrate(Constants::DIG_DIRECTION dir) override;
		void pickUpGold(std::vector<Tile*>& tiles) override;
		void choosePath(std::vector<Tile*>& tiles) override {}
    private:

};

#endif // HERO_H
