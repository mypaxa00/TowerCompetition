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
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	Shadow() = default;

	Shadow(std::string id) : id(id) {}

	~Shadow() {
	}

	void setTex(std::string id) {
		this->id = id;
		texture = Game::assets->GetTexture(id);
	}

	void init() override {
		setTex(id);
		angle = &entity->getComponent<SpriteComponent>().angle;
		dest = &entity->getComponent<SpriteComponent>().getDestRect;
		transform = &entity->getComponent<TransformComponent>();
		src.h = transform->height / transform->scale;
		src.w = transform->width / transform->scale;
		src.x = src.y = 0;
	}

	void draw() override {
		TextureManager::Draw(texture, src, *dest, flip, *angle);
	}

private:
	TransformComponent * transform;
	SDL_Texture *texture;
	SDL_Rect src, * dest;
};
