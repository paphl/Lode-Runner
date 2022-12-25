#include "..\include\AnimateTile.h"

AnimateTile::AnimateTile(int x, int y, int width, int height, std::string type)
{

	texture = ResourceHolder::Acquire(Texture_Paths::Tileset);
	if (type == "Rope" || type == "Stone" || type == "Ladder")
	{
		this->nFrames = 1;
		for (int i = 0; i < nFrames; i++)
		{
			frames.push_back({ x + i * width, y,  width,  height });
		}
	}
	else if (type == "Dirt")
	{
		this->nFrames = 11;
		int temp = 0;

		//this is done because of my sprite sheet, get the basic visu of the dirt tile and the decompose animation as well
		frames.push_back({ x, y,  width,  height });
		y += height;

		for (int i = 2; i < nFrames; i++)
		{
			frames.push_back({ x + temp*width, y,  width,  height });
			temp = i % 2;
			if (temp == 1)
			{
				y += height;
			}
		}
	}
	else if (type == "Gold")
	{
		this->nFrames = 3;

		for (int i = 0; i < nFrames; i++)
		{
			frames.push_back({ x , y + i * height,  width,  height });
		}
	}

}

void AnimateTile::ApplyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setScale(4.0f, 4.0f);
}

void AnimateTile::Advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}
