#include "..\include\Tile.h"

void Tile::Draw(sf::RenderTarget& window)
{
    window.draw(sprite);
}

void Tile::init(float xPos, float yPos)
{
    /*
	texture =  ResourceHolder::Acquire(Texture_Paths::Tileset);
    sprite.setPosition(position);*/

	position = sf::Vector2f(xPos, yPos);

	sprite.setTextureRect({ 0,0,64,64 });
	sprite.setScale(4.0f, 4.0f);
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
	return isBlocking;
}

bool Tile::getIsVisible()
{
	return isVisible;
}
void Tile::setIsVisible(bool isVis)
{
	isVisible = isVis;
}

std::string Tile::getTileType()
{
	return type;
}

void Tile::Update(float dt)
{
	animation.Update(dt);
	animation.ApplyToSprite(sprite);
}

void Tile::setFrame(int frame)
{
	this->animation.setFrame(frame);
	animation.ApplyToSprite(sprite);
}

int Tile::getFrame()
{
	return this->animation.getFrame();
}
