#ifndef __io__
#define __io__

#include <iostream>
#include <memory>

using namespace std;

#endif

#include "..\include\Tile.h"

enum TILE_TYPE
{
	DIRT = 0,
	STONE,
	LADDER,
	ROPE,
	GOLD
};

class TileFactory
{
public:
    static Tile * createTile(TILE_TYPE type, float xPos, float yPos)
    {
        Tile * tile = NULL;
        switch(type)
        {
		case TILE_TYPE::DIRT:
            {
                tile = new Dirt;
                break;
            }
        case TILE_TYPE::STONE:
            {
                tile = new Stone;
                break;
            }
        case TILE_TYPE::LADDER:
            {
                tile = new Ladder;
                break;
            }
        case TILE_TYPE::ROPE:
            {
                tile = new Rope;
                break;
            }
		case TILE_TYPE::GOLD:
		{
			tile = new Gold;
			break;
		}
        default:
            {
                cout << "invalid tile type please re-enter type" << endl;
                return NULL;
            }
        }
        tile->init(xPos, yPos);
		return tile;
    }

};
