#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class ResourceHolder
{
public:
    static std::shared_ptr<sf::Texture> Acquire( const std::string& name);
    static void collectGarbage(); //removes texture not used from our memory;

private:
    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
};


