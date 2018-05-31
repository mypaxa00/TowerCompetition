#pragma once
#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"

class Shadow : public Component
{
public:

	std::string id;
	float * angle;

	Shadow() = default;

	Shadow(Manager * man, std::string id) : id(id), man(man) {}

	~Shadow() {
		sh->destroy();
	}

	void init() override {
		sh = &man->addEntity();
		angle = &entity->getComponent<SpriteComponent>().angle;
		transform = &entity->getComponent<TransformComponent>().position;
		sh->addComponent<TransformComponent>();
		sh->addComponent<SpriteComponent>(id);
		sprite = &sh->getComponent<SpriteComponent>();
		position = &sh->getComponent<TransformComponent>().position;
		sh->addGroup(Game::G_Shadows);
	}

	void update() override {
		position->x = 10 + transform->x;
		position->y = 10 + transform->y;
		sprite->angle = *angle;
	}

private:
	Entity * sh;
	SpriteComponent * sprite;
	Vector2D * transform;
	Vector2D * position;
	Manager * man;
};
