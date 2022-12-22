#include "..\include\Tile.h"

void Tile::Draw(sf::RenderTarget& window)
{
    window.draw(sprite);
}

void Tile::init(float xPos, float yPos)
{
    position = sf::Vector2f(xPos,yPos);
	texture =  ResourceHolder::Acquire(Texture_Paths::Tileset);
    sprite.setPosition(position);
}

sf::Vector2f Tile::getPosition()
{
	return position;
}
void Tile::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
	position = pos;
}

const float  Tile::getSize()
{
	return sprite.getGlobalBounds().width;
}

sf::FloatRect Tile::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}


const bool  Tile::getIsBlocking()
{
	return canDestroy;
}

bool Tile::getIsVisible()
{
	return isVisible;
}
void Tile::setIsVisible(bool isVis)
{
	isVisible = isVis;
}
