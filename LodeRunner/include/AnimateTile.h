#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include<SFML/Graphics.hpp>

#include "FilePaths.h"
#include "ResourceHolder.h"

class AnimateTile {
public:
	AnimateTile() = default;
	AnimateTile(int x, int y, int width, int height, std::string type);
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
	int nFrames = 0;
	static constexpr float holdTime = 0.3f; //time a frame will be on  screen
	std::shared_ptr<sf::Texture> texture;
	std::vector<sf::IntRect> frames;
	int iFrame = 0; //index of current frame
	float time = 0.0f; //track time elapsed till text animation
};
