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

