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
	static void MapPreload(int sizeX = 30, int sizeY = 16);
	static void MapPostload(int sizeX = 30, int sizeY = 16);
};

