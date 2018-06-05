#pragma once

#include <SDL.h>
#include "../AssetManager.h"
#include "Components.h"
#include <sstream>

class TowerUpgrade : public Component
{
public:
	TowerUpgrade(Manager * man) : manager(man) {}
	~TowerUpgrade() {}

	void init() override {
		lvl = entity->getComponent<EnemyDetect>().level;
		entity->addComponent<MouseButtonComponent>();
		mouse = &entity->getComponent<MouseButtonComponent>();
		pos = entity->getComponent<TransformComponent>().position;
		type = entity->getComponent<EnemyDetect>().type;
	}

	void update() override {
		if (mouse->see) {
			if (selection == NULL) {
				selection = &manager->addEntity();
				selection->addComponent<TransformComponent>(pos.x, pos.y);
				selection->addComponent<SpriteComponent>("selection");
				selection->addGroup(Game::G_Towers);
			}
			chekButton();
		}
		else {
			if (selection != NULL) {
				selection->destroy();
				selection = NULL;
			}
		}
	}

private:
	Manager * manager;
	int lvl;
	AssetManager::TowersType type;
	MouseButtonComponent * mouse;
	Entity* selection = NULL;
	Vector2D pos;

	void chekButton() {
		if(mouse->pressed1)
			switch (type)
			{
			case AssetManager::Tw_MashineGun: {
				if (Game::money >= (100 + 25 * lvl)) {
					Game::money -= (100 + 25 * lvl);
					entity->getComponent<EnemyDetect>().level++;
					lvl++;
					Game::assets->CreateTower(entity->getComponent<TransformComponent>().position,
						type, 250, 15, lvl);
					selection->destroy();
					selection = NULL;
					entity->delGroup(Game::G_Towers);
					entity->destroy();
					return;
				}
				break;
			}
			case AssetManager::Tw_RocketLauncher:
				if (Game::money >= 150 + 50 * lvl) {
					Game::money -= 150 + 50 * lvl;
					entity->getComponent<EnemyDetect>().level++;
					lvl++;
					Game::assets->CreateTower(entity->getComponent<TransformComponent>().position,
							type, 350, 7, lvl);
					selection->destroy();
					selection = NULL;
					entity->delGroup(Game::G_Towers);
					entity->destroy();
					return;
				}
				break;
			}
	}
};