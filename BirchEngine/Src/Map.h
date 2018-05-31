#pragma once
#include <SDL.h>
#include <string>
#include <fstream>
#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	static void LoadMap(int sizeX = 30, int sizeY = 16);


};

