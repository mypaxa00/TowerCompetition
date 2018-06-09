#pragma once

#include "ESC.h"
#include "Components.h"
#include "../Collision.h"
#include <vector>
#include <sstream>

class HealthComponent : public Component
{
public:

	int maxHealth;

	HealthComponent(Manager * man, int hlth) : manager(man), maxHealth(hlth){}
	~HealthComponent(){}

	void init() override {
		position = &entity->getComponent<TransformComponent>().position;
		shot = &manager->getGroup(Game::G_Projectiles);
		label = &manager->addEntity();
		health = maxHealth;
		std::stringstream hlth;
		hlth << health;
		label->addComponent<UILabel>(position->x, position->y, hlth.str(), "Future18", green);
		label->addGroup(Game::G_Labels);
	}

	void update() override;

private:
	int health;
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_Color yellow = { 255, 255, 0, 255 };
	SDL_Color red = { 255, 0, 0, 255 };
	Entity * label;
	Manager * manager;
	Vector2D * position;
	std::vector<Entity *> * shot;
};