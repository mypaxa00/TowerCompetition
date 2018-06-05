#include "Map.h"
#include "TextureManager.h"
#include "SDL.h"
#include <cctype>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>


Map::Map()
{
}


Map::~Map()
{
}

void Map::LoadMap(int sizeX, int sizeY)
{

	char tile;
	std::fstream mapFile;
	mapFile.open(Game::map);
	int count = 0;
	std::string map = "";
	do {
		mapFile.get(tile);
		if (tile != ' ' && tile != '\t')
			map += tile;
		if (tile == '\n')
			count++;
	} while (count < sizeY);
	mapFile.close();

	mapFile.open(Game::decorations);
	count = 0;
	std::string dcr = "";
	do {
		mapFile.get(tile);
		if (tile != ' ' && tile != '\t')
			dcr += tile;
		if (tile == '\n')
			count++;
	} while (count < sizeY);
	mapFile.close();

	size_t pos = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{		
			std::string x;
			while (isdigit(map.at(pos))) {
				x += map.at(pos);
				pos++;
			}
			pos++; 
			Game::AddTile(atoi(x.c_str()), j * 64, i * 64);
		}
	}

	std::cout << dcr << std::endl;
	pos = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			std::string x;
			while (isdigit(dcr.at(pos))) {
				x += dcr.at(pos);
				pos++;
			}
			pos++;
			Game::AddDecoration(atoi(x.c_str()), j * 64, i * 64);
		}
	}

	mapFile.open(Game::trajectory);
	count = 0;
	std::string trj = "";
	do {
		mapFile.get(tile);
		if (tile != ' ' && tile != '\t')
			trj += tile;
		if (tile == '\n')
			count++;
	} while (count < 1);
	mapFile.close();

	pos = 0;
	for (int i = 0; i < Game::checkPointCount; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			std::string x;
			while (isdigit(trj.at(pos))) {
				x += trj.at(pos);
				pos++;
			}
			pos++;
			Game::trajectorys[i][j] = atoi(x.c_str());
		}
	}
}
