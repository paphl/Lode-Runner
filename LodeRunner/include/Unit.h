#ifndef UNIT_H
#define UNIT_H
#include <iostream>
#include <memory>
#include<SFML/Graphics.hpp>

#include "FilePaths.h"
#include "ResourceHolder.h"
#include "AnimateUnit.h"
#include "Tile.h"
/*
class AnimateUnit {
public:
	AnimateUnit() = default;
	AnimateUnit(int x, int y, int width, int height);
	void ApplyToSprite(sf::Sprite& s) const;
	void Update(float dt)
	{
		time += dt;
		while (time >= holdTime)
		{
			time -= holdTime;
			Advance();
		}
	}
private:
	void Advance();
	static constexpr int nFrames = 4;
	static constexpr float holdTime = 0.1f; //time a frame will be on  screen
	std::shared_ptr<sf::Texture> texture;
	sf::IntRect frames[nFrames];
	int iFrame = 0; //index of current frame
	float time = 0.0f; //track time elapsed till text animation
};
*/
class Unit
{
	protected:
		enum class AnimationIndex
		{
			Climb,
			RopeLeft,
			RopeRight,
			WalkingRight,
			WalkingLeft,
			Falling,
			DisintegrateLeft,
			DisintegrateRight,
			Count
		};
    public:
		virtual ~Unit() {}
		virtual std::unique_ptr<Unit> clone() = 0;
		Unit(const sf::Vector2f& pos);
		void Draw(sf::RenderTarget& rt) const;
		void SetDirection(const sf::Vector2f& dir);
		void Update(float dt);
		virtual void Disintegrate(Constants::DIG_DIRECTION dir) = 0;
		void setPosition(sf::Vector2f position);
		bool isColliding(sf::FloatRect fr,  float precision = 1.5f);
		sf::Vector2f getPosition();
		bool GravityPull(std::vector<Tile*>& tiles);
		bool getIsFalling();
		void setIsFalling(bool isFalling);
		virtual void pickUpGold(std::vector<Tile*>& tiles) = 0;
		virtual void choosePath(std::vector<Tile*>& tiles) = 0;
		int getGoldCounter();
		sf::FloatRect getGlobalBounds() const
		{
			return sprite.getGlobalBounds();
		}
		void setPos(float x = 0, float y = 0)
		{
			this->pos = sf::Vector2f(x, y);
		}
		bool getOnRope();
		void setOnRope(bool onRope);
		bool getIsVisible();
		void setIsVisible(bool isVisible);
    protected:
		static constexpr float speed = 100.0f;
		sf::Vector2f pos;
		sf::Vector2f vel = { 0.0f, 0.0f };
		sf::Vector2f dir = { 0.0f, 0.0f };
		sf::Sprite sprite;
		sf::Clock clock;
		bool isFalling = false;
		int direction;
		bool onRope = false;
		int goldCounter = 0;
		bool isVisible = true;
		//sf::FloatRect collisionRect;
		AnimateUnit animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation = AnimationIndex::WalkingLeft;
};


#endif // UNIT_H
