#include "..\include\Unit.h"


Unit::Unit(const sf::Vector2f& position)
{
	pos = position;
	
	clock.restart();
	sprite.setTextureRect({ 0,0,64,64 });
	sprite.setScale(4.0f, 4.0f);

}

void Unit::Draw(sf::RenderTarget& rt) const
{
	rt.draw(sprite);

}

void Unit::SetDirection(const sf::Vector2f& dir)
{
	vel = dir * speed;
	if (!onRope)
	{
		if (dir.x > 0.0f)
		{
			curAnimation = AnimationIndex::WalkingRight;
		}
		if (dir.x < 0.0f)
		{
			curAnimation = AnimationIndex::WalkingLeft;
		}
	}
	else
	{
		if (dir.x > 0.0f)
		{
			curAnimation = AnimationIndex::RopeRight;

		}
		if (dir.x < 0.0f)
		{
			curAnimation = AnimationIndex::RopeLeft;
		}
	}

	
	if ((dir.y < 0.0f || dir.y > 0.0f) && !isFalling)
	{
		curAnimation = AnimationIndex::Climb;

	}

	if (dir.y > 0.0f && isFalling)
	{
		curAnimation = AnimationIndex::Falling;
	}
}

void Unit::Update(float dt)
{

	pos += vel * dt;
	animations[int(curAnimation)].Update(dt);
	animations[int(curAnimation)].ApplyToSprite(sprite);
	sprite.setPosition(pos);

}

void Unit::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
	pos = position;
}

sf::Vector2f Unit::getPosition()
{
	return pos;
}

bool Unit::isColliding(sf::FloatRect fr, float precision)
{
	sf::FloatRect collisionRect = sprite.getGlobalBounds();
	collisionRect.top -= precision;
	collisionRect.height += precision;
	collisionRect.left -= precision;
	collisionRect.width += precision;

	return collisionRect.intersects(fr);
}

bool Unit::GravityPull(std::vector<Tile*>& tiles)
{
	//making small point to the collision to be more precize
	//sf::FloatRect bottomLeftPoint;


	
//	sf::FloatRect bottomRightPoint;
	

	for (int i = 0; i < tiles.size(); i++)
	{
		if (this->isColliding(tiles[i]->getGlobalBounds(), -4.0f) && !(tiles[i]->getTileType() == "Gold") && !(tiles[i]->getTileType() == "Rope") && tiles[i]->getIsVisible())
		{
			return true;
		}
	}
	return false;
}

bool Unit::getIsFalling()
{
	return isFalling;
}

void Unit::setIsFalling(bool isFalling)
{
	this->isFalling = isFalling;
}


bool Unit::getOnRope()
{
	return onRope;
}

void Unit::setOnRope(bool onRope)
{
	this->onRope = onRope;
}

int Unit::getGoldCounter()
{
	return goldCounter;
}

bool Unit::getIsVisible()
{
	return isVisible;
}

void Unit::setIsVisible(bool isVisible)
{
	this->isVisible = isVisible;
}