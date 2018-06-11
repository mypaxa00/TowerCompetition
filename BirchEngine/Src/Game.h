#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <iostream>
#include <vector>
#include <string>
#include "ESC/ESC.h"



class AssetManager;
//class ColliderComponent;

class Game
{
public:
	Game();
	~Game();



	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int id, int x, int y);
	static void AddDecoration(int id, int x, int y);
	static SDL_Renderer * renderer;
	static AssetManager * assets;
	static SDL_Event event;
	static bool isRunning;
	
	static TCPsocket server;
	static TCPsocket client;

	static int type;
	static std::string IP;
	static int command;

	enum groupLabels : std::size_t {
		G_Map,
		G_Decorations,
		G_Players,
		G_Towers,
		G_Enemies,
		G_Colliders,
		G_Projectiles,
		G_Labels,
		G_Shadows,
		G_UpgradeMenue,
		G_Buttons,
		G_BGs
	};
	enum StartAs : int
	{
		S_Server,
		S_Client
	};
	enum Commands : int 
	{
		C_NONE,
		C_SEND_S1,
		C_SEND_S2,
		C_SEND_S3,
		C_SEND_S4,
		C_SEND_P1,
		C_SEND_P2,
		C_WIN
	};

	static int health;
	static float money;
	static int exp;
	static int moneySpeed;
	static std::string map;
	static std::string decorations;
	static std::string trajectory;
	static int trajectorys[32][2];
	static int checkPointCount;
	
private:
	int prevSpawnTime;
	bool connected = false;
	SDL_Window *window;
};