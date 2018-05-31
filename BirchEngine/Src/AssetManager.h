#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ESC/ESC.h"
#include <SDL_ttf.h>

class AssetManager
{
public:

	enum ShotType
	{
		Sh_Bullet1,
		Sh_Bullet2,
		Sh_Bullet3,
		Sh_Bullet4,
		Sh_Rocket1,
		Sh_Rocket2
	};

	enum ButtonColor
	{
		B_Blue,
		B_Green,
		B_White,
		B_Red,
		B_Yellow
	};

	enum TowersType
	{
		Tw_MashineGun,
		Tw_RocketLauncher
	};

	enum EnemyType
	{
		E_Soldier1,
		E_Soldier2,
		E_Soldier3,
		E_Soldier4,
		E_Plane1,
		E_Plane2
	};

	AssetManager(Manager * man);
	~AssetManager();

	Entity * CreateButton(int posX, int posY, int width, int height, std::string text, ButtonColor color = B_Blue);

	void CreateTowerPlace(Vector2D pos, std::string id);

	void CreateTower(Vector2D pos, TowersType type, int range, float speed, int lvl = 1);

	Entity * CreateProjectile(Vector2D pos, Vector2D vel, int range, float speed, ShotType bull, float* ang = NULL, Vector2D* enemy = NULL);

	void CreateEnemy(EnemyType enemy = E_Soldier1);

	void AddTexture(std::string id, const char* path);
	SDL_Texture * GetTexture(std::string id);
	void AddFont(std::string id, const char* path, int fontSize);
	TTF_Font * GetFont(std::string id);


private:

	Manager * manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
 
};

