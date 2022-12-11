#include <iostream>
#include <vector>
#include "Tile.h"

using namespace std;

struct Level
{
    vector<Tile> tiles;
    void setTiles(vector<Tile> v)
    {
        tiles = v;
    }

    vector<Tile> getTiles()
    {
        return tiles;
    }
};
