#pragma once

#include <SDL.h>
#include "ESC.h"
#include "Components.h"
#include "../AssetManager.h"

class TowerPlaceComponent : public Component
{
public:
	TowerPlaceComponent(Manager * man) : manager(man) {}
	~TowerPlaceComponent(){}

	void init() override {
		mouse = &entity->getComponent<MouseButtonComponent>();
		pos = entity->getComponent<TransformComponent>().position;
	}

	void update() override {
		if (mouse->see) {
			if (selection == NULL) {
				selection = &manager->addEntity();
				selection->addComponent<TransformComponent>(pos.x, pos.y);
				selection->addComponent<SpriteComponent>("selection");
				selection->addGroup(Game::G_Towers);
			}
			chekButtons();
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
	MouseButtonComponent * mouse;

	Vector2D pos;

	Entity* selection = NULL;

	void clearButtons(bool full = false) {
		selection->destroy();
		if (full)
			entity->destroy();
	}

	void chekButtons() {
		if (Game::money >= 100 && mouse->pressed1) {
			Game::assets->CreateTower(pos, AssetManager::Tw_MashineGun, 250, 15);
			Game::money -= 100;
			clearButtons(true);
			return;
		}
		if (Game::money >= 150 && mouse->pressed2) {
			Game::assets->CreateTower(pos, AssetManager::Tw_RocketLauncher, 350, 7);
			Game::money -= 150;
			clearButtons(true);
			return;
		}
	}
};
