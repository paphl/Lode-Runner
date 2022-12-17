#ifndef UNIT_H
#define UNIT_H
#include <iostream>
#include <memory>
#include<SFML/Graphics.hpp>

#include "FilePaths.h"
#include "ResourceHolder.h"
#include "Tile.h"

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

class Unit
{
	protected:
		enum class AnimationIndex
		{
			Climb,
			WalkingRight,
			WalkingLeft,
			Falling,
			Disintegrate,
			Count
		};
    public:
		virtual ~Unit() {}
		virtual std::unique_ptr<Unit> clone() = 0;
		Unit(const sf::Vector2f& pos);
		void Draw(sf::RenderTarget& rt) const;
		void SetDirection(const sf::Vector2f& dir);
		void Update(float dt);
		virtual void Disintegrate() = 0;
		void setPosition(sf::Vector2f position);
		bool isColliding(sf::FloatRect fr);
		sf::Vector2f getPosition();
		bool GravityPull(std::vector<Tile*>& tiles);
		bool getIsFalling();
		void setIsFalling(bool isFalling);
		sf::FloatRect getGlobalBounds() const
		{
			return sprite.getGlobalBounds();
		}
		void setPos(float x = 0, float y = 0)
		{
			this->pos = sf::Vector2f(x, y);
		}
    protected:
		static constexpr float speed = 100.0f;
		sf::Vector2f pos;
		sf::Vector2f vel = { 0.0f, 0.0f };
		sf::Sprite sprite;
		bool isFalling = false;
		//sf::FloatRect collisionRect;
		AnimateUnit animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation = AnimationIndex::WalkingLeft;
};


#endif // UNIT_H
