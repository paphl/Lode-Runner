#include "..\include\Unit.h"

AnimateUnit::AnimateUnit(int x, int y, int width, int height)
{

	texture = ResourceHolder::Acquire(Texture_Paths::Characters);

	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { x + i*width, y,  width,  height};
	}
}

void AnimateUnit::ApplyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
}

void AnimateUnit::Advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}

Unit::Unit(const sf::Vector2f& position)
{
	pos = position;
	
	
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
	if (dir.x > 0.0f)
	{
		curAnimation = AnimationIndex::WalkingRight;
	}
	if (dir.x < 0.0f)
	{
		curAnimation = AnimationIndex::WalkingLeft;
	}
	
	if (dir.y < 0.0f || dir.y > 0.0f)
	{
		curAnimation = AnimationIndex::Climb;

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

bool Unit::isColliding(sf::FloatRect fr)
{
	sf::FloatRect collisionRect = sprite.getGlobalBounds();
	collisionRect.top -= 1.0f;
	collisionRect.height += 1.0f;
	collisionRect.left -= 1.0f;
	collisionRect.width += 1.0f;
	if (collisionRect.intersects(fr))
	{
		return true;
	}
	return false;
}

bool Unit::GravityPull(std::vector<Tile*>& tiles)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (this->isColliding(tiles[i]->getGlobalBounds()) && !(tiles[i]->getTileType() == "Gold") && !(tiles[i]->getTileType() == "Rope"))
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