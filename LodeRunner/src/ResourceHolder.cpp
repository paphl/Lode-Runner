#include "..\include\ResourceHolder.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> ResourceHolder::pTextures; //static have to be declared ourside of the class bs

std::shared_ptr<sf::Texture> ResourceHolder::Acquire( const std::string& name)
{
        const auto i = pTextures.find(name);
        if(i != pTextures.end())
        {
            return i->second;
        }
        else
        {
            auto pTex = std::make_shared<sf::Texture>();
            pTex->loadFromFile(name);
            pTextures.insert({name, pTex});
            return pTex;
        }
}

void ResourceHolder::collectGarbage() //removes texture not used from our memory;
    {
        for(auto i = pTextures.begin(); i != pTextures.end();)
        {
            if(i->second.unique()) //checks if the texture ptr is used only by the ResourceHolder
            {
                i = pTextures.erase(i); //
            }
            else
            {
                ++i;
            }
        }
    }
