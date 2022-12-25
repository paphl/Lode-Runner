#ifndef TILE_H
#define TILE_H
#include<SFML/Graphics.hpp>

#include "ResourceHolder.h"
#include "FilePaths.h"
#include "AnimateTile.h"

class Tile
{
    public:
        virtual void init(float xPos, float yPos);
        void Draw(sf::RenderTarget& window);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f pos);
		const float  getSize();
		sf::FloatRect getGlobalBounds() const;
		const bool  getIsBlocking();
		bool getIsVisible();
		void setIsVisible(bool isVis);
		std::string getTileType();
		void Update(float dt);
		void setFrame(int frame);
		int getFrame();
    protected:
        sf::Vector2f position;
        sf::Sprite sprite;
        std::shared_ptr<sf::Texture> texture;
        bool canDestroy;
		std::string type;
		bool isBlocking = false; //false if the unit can pass through the specific tile
		bool isVisible = true;
		AnimateTile animation;
};

class Dirt: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
			Tile::init(xPos, yPos);
			/*sprite.setTexture(*texture);
			sprite.setTextureRect({ 0,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);*/
			type = "Dirt";
			animation = AnimateTile(0,0, Constants::Unit_Size, Constants::Unit_Size,type);
			animation.ApplyToSprite(this->sprite);
            canDestroy = true;
			isBlocking = true;
        }

};

class Stone: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			/*sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);*/
			type = "Stone";
			animation = AnimateTile(Constants::Unit_Size, 0, Constants::Unit_Size, Constants::Unit_Size, type);
			animation.ApplyToSprite(this->sprite);

            canDestroy = false;
			isBlocking = true;
        }

};

class Ladder : public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			/*sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16*2, 0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);*/
			type = "Ladder";
			animation = AnimateTile(Constants::Unit_Size * 2, 0, Constants::Unit_Size, Constants::Unit_Size, type);
			animation.ApplyToSprite(this->sprite);

            canDestroy = false;
        }

};

class Rope: public Tile
{
    public:
        void init(float xPos, float yPos)
        {
                //set tile size and texture
			Tile::init(xPos, yPos);
			/*sprite.setTexture(*texture);
			sprite.setTextureRect({ Constants::I_16*3,0,Constants::I_16,Constants::I_16 });
			sprite.setScale(4.0f, 4.0f);*/
			type = "Rope";
			animation = AnimateTile(Constants::I_16 * 3, 0, Constants::I_16, Constants::I_16, type);
			animation.ApplyToSprite(this->sprite);

            canDestroy = false;
        }

};

class Gold : public Tile
{
public:
	void init(float xPos, float yPos)
	{
		//set tile size and texture
		Tile::init(xPos, yPos);
		/*sprite.setTexture(*texture);
		sprite.setTextureRect({ Constants::I_16*6,0,Constants::I_16,Constants::I_16 });
		sprite.setScale(4.0f, 4.0f);*/
		type = "Gold";
		animation = AnimateTile(Constants::I_16 * 6, 0, Constants::I_16, Constants::I_16, type);
		animation.ApplyToSprite(this->sprite);

		canDestroy = false;
	}

};
#endif // TILE_H
