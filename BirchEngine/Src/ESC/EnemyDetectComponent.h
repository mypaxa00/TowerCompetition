#pragma once

#include "Components.h"
#include "../AssetManager.h"
#include "ESC.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <cmath>

class EnemyDetect : public Component
{
public:

	AssetManager::TowersType type;
	int level;
	int fireRate;

	EnemyDetect(Manager * man, AssetManager::TowersType tp, int rng, float spd, int lvl) 
		: manager(man), range(rng), level(lvl), speed(spd), type(tp)
	{
	}
	~EnemyDetect(){}

	void init() override {
		position = entity->getComponent<TransformComponent>().position;
		enemies = &manager->getGroup(Game::G_Enemies);
		bullet = &manager->addEntity();
		bullet->destroy();
		switch (type)
		{
		case AssetManager::Tw_MashineGun:
			fireRate = 250;
			break;
		case AssetManager::Tw_RocketLauncher:
			switch (level)
			{
			case 1:
				fireRate = 2000;
				break;
			case 2:
				fireRate = 1500;
				break;
			case 3:
				fireRate = 3000;
				break;
			}
			break;
		default:
			break;
		}
	}

	void update() override {

		delay = static_cast<int>((SDL_GetTicks() / fireRate) % 2);

		//Chek Enemy
		if (curEnemy == NULL || curEnemy->isActive() != 1 || !curEnemy->hasGroup(Game::G_Enemies)) {
			FindEnemy();
			return;
		}

		//Find Enemy pos
			Vector2D enemiePos = curEnemy->getComponent<TransformComponent>().position;
			dir = Vector2D(enemiePos.x - position.x, enemiePos.y - position.y);
			distance = sqrt(pow(dir.x, 2) + pow(dir.y, 2));

		//Chek range
		if (distance > range) {
			FindEnemy();
			return;
		}

		//Angle
		float * angle = &entity->getComponent<SpriteComponent>().angle;
			*angle = asin((dir.x) / distance) * 180 / M_PI;
			if (dir.y > 0) {
				if (dir.x > 0)
					*angle = 180 - *angle;
				else
					*angle = -180 - *angle;
			}
		
		//Fire
		if (delay != prev) {
			prev = delay;
			Vector2D enemiePos = curEnemy->getComponent<TransformComponent>().position;
			Vector2D vel = Vector2D(enemiePos.x - position.x, enemiePos.y - position.y);

			switch (type)
			{
			case AssetManager::Tw_MashineGun:
				switch (level)
				{
				case 1:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Bullet1);
					break;
				case 2:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Bullet2);
					break;
				case 3:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Bullet3);
					break;
				case 4:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Bullet4);
					break;
				default:
					break;
				}
				break;
			case AssetManager::Tw_RocketLauncher:
				switch (level)
				{
				case 1:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Rocket1, angle, curEnemy);
					break;
				case 2:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Rocket2, angle, curEnemy);
					break;
				case 3:
					bullet = Game::assets->CreateProjectile(position, vel, range, speed, AssetManager::Sh_Rocket3, angle, curEnemy);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
		
				
	}

private:
	int range;
	float speed;
	float distance;

	int delay;
	int prev = 0;

	Manager * manager;
	Entity * curEnemy = NULL;
	Entity * bullet;
	Vector2D dir;
	Vector2D position;
	std::vector<Entity*>* enemies;

	void FindEnemy() {
		curEnemy = NULL;
		prev = delay;
		for (auto& e : *enemies) {
			if (e->isActive() == 1) {
				Vector2D enemiePos = e->getComponent<TransformComponent>().position;
				float distance = sqrt(pow(enemiePos.x - position.x, 2) + pow(enemiePos.y - position.y, 2));
				if (distance < range) {
					curEnemy = e;
					Vector2D vel = Vector2D(enemiePos.x - position.x, enemiePos.y - position.y);
					break;
				}
			}
		}
	}

};