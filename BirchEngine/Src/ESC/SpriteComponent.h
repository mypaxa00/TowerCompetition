#pragma once
#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
public:

	std::string id;
	float angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id, float ang = NULL, Vector2D sz = Vector2D(0, 0)) : angle(ang), size(sz)
	{
		setTex(id);
	}

	~SpriteComponent() {
	}

	void setTex(std::string id) {
		this->id = id;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		if (size.x == 0 && size.y == 0) {
			src.h = transform->height / transform->scale;
			src.w = transform->width / transform->scale;
		}
		else {
			src.h = size.y;
			src.w = size.x;
		}
		src.x = src.y = 0;
	}

	void update() override {
		dest.h = static_cast<int>(transform->height * transform->scale);
		dest.w = static_cast<int>(transform->width * transform->scale);
		dest.x = transform->position.x;
		dest.y = transform->position.y;
	}

	void draw() override {
		texture = Game::assets->GetTexture(id);
		TextureManager::Draw(texture, src, dest, flip, angle);
	}

	SDL_Rect getDestRect() {
		return dest;
	}

private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect src, dest;
	Vector2D size;
	bool aniamated = false;
	int frames = 0;
	int speed = 100;
};
