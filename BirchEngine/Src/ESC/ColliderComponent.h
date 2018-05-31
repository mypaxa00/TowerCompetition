#pragma once

#include "Components.h"
#include "ESC.h"
#include <SDL.h>
#include <string>

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;
	int width;
	int height;

	TransformComponent* transform;
	SpriteComponent * sprite;

	ColliderComponent(std::string t, int w = 64, int h = 64) : width(w), height(h)
	{
		tag = t;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();
		collider.w = width;
		collider.h = height;
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x + (transform->width - width) / 2);
		collider.y = static_cast<int>(transform->position.y + (transform->height - height) / 2);
	}

};

