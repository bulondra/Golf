#include <iostream>
#include <vector>
#include "Level.h"

using namespace std;

struct Levels
{
    vector<Level> levels;
    void setLevels(vector<Level> v)
    {
        levels = v;
    }

    vector<Level> getLevels()
    {
        return levels;
    }
};
