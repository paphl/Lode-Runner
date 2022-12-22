#ifndef TILE_H
#define TILE_H
#include<SFML/Graphics.hpp>

#include "ResourceHolder.h"
#include "FilePaths.h"

class Tile
{
    public:
        virtual void init(float xPos, float yPos);
        void Draw(sf::RenderTarget& window);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f pos);
		const float  getSize();
		sf::FloatRect getGlobalBounds() const;
		virtual std::string getTileType() = 0;
		const bool  getIsBlocking();
		bool getIsVisible();
		void setIsVisible(bool isVis);
    protected:
		static constexpr int nFrames = 4;
        sf::Vector2f position;
        sf::Sprite sprite;
        std::shared_ptr<sf::Texture> texture;
        bool canDestroy;
		bool isBlocking = false; //false if the unit can pass through the specific tile
		bool isVisible = true;

};

class Dirt: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
			Tile::init(xPos, yPos);
			sprite.setTexture(*texture);
			sprite.setTextureRect({ 0,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);
            canDestroy = true;
			isBlocking = true;
        }

		std::string getTileType()
		{
			return "Dirt";
		}
};

class Stone: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);
            canDestroy = false;
			isBlocking = true;
        }

		std::string getTileType()
		{
			return "Stone";
		}
};

class Ladder : public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16*2, 0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);
            canDestroy = false;
        }

		std::string getTileType()
		{
			return "Ladder";
		}
};

class Rope: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16*3,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);
            canDestroy = false;
        }

		std::string getTileType()
		{
			return "Rope";
		}
};

class Gold : public Tile
{
public:
	void init(float xPos, float yPos)
	{
		//set tile size and texture
		Tile::init(xPos, yPos);
		sprite.setTexture(*texture);
		sprite.setTextureRect({ Constants::I_16*6,0,Constants::I_16,Constants::I_16 });
		sprite.setScale(4.0f, 4.0f);
		canDestroy = false;
	}

	std::string getTileType()
	{
		return "Gold";
	}

	std::string get1()
	{
		return "Gold";
	}
};
#endif // TILE_H
