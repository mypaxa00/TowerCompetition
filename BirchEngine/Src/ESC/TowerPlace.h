#pragma once

#include <SDL.h>
#include "ESC.h"
#include "Components.h"
#include "../AssetManager.h"

class TowerPlaceComponent : public Component
{
public:
	TowerPlaceComponent(Manager * man, AssetManager * ast) : manager(man), asset(ast)
	{
	}
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
	AssetManager * asset;
	MouseButtonComponent * mouse;

	Vector2D pos;

	Entity* selection = NULL;

	bool menuShows = false;

	void showMenu() {

	}

	void clearButtons(bool full = false) {
		menuShows = false;
		selection->destroy();
		if (full)
			entity->destroy();
	}

	void chekButtons() {
		if (Game::money >= 100 && mouse->pressed1) {
			asset->CreateTower(pos, AssetManager::Tw_MashineGun, 250, 15);
			Game::money -= 100;
			clearButtons(true);
			return;
		}
		if (Game::money >= 175 && mouse->pressed2) {
			asset->CreateTower(pos, AssetManager::Tw_RocketLauncher, 350, 4);
			Game::money -= 175;
			clearButtons(true);
			return;
		}
	}
};
