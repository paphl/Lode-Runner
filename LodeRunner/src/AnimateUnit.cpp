#include "..\include\AnimateUnit.h"

AnimateUnit::AnimateUnit(int x, int y, int width, int height)
{

	texture = ResourceHolder::Acquire(Texture_Paths::Characters);

	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { x + i * width, y,  width,  height };
	}
}

void AnimateUnit::ApplyToSprite(sf::Sprite& s) const
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
}

void AnimateUnit::Advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}
