#ifndef HERO_H
#define HERO_H

#include "Unit.h"

class Hero : public Unit
{
    public:
		Hero(const sf::Vector2f& position);
		std::unique_ptr<Unit> clone() override;
		void Disintegrate() override;
    private:

};

#endif // HERO_H
