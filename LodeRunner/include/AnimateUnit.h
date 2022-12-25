#pragma once
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
