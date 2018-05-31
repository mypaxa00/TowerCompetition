#pragma once

#include "../Game.h"
#include "ESC.h"
#include "Components.h"


class KeyBoardController : public Component
{
public:
	TransformComponent * transform;
	SpriteComponent * sprite;
	
	float speed;

	KeyBoardController(float speed) {
		this->speed = speed;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		transform->speed = speed;
		angle = &sprite->angle;
	}

	void update() override {

		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = -10;
				break;
			case SDLK_w:
				transform->velocity.y = -10;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 10;
				break;
			case SDLK_s:
				transform->velocity.y = 10;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 10;
				break;
			case SDLK_d:
				transform->velocity.x = 10;
				break;
			case SDLK_LEFT:
				transform->velocity.x = -10;
				break;
			case SDLK_a:
				transform->velocity.x = -10;
				break;
			case 61:
				speed++;
				transform->speed = speed;
				break;
			case SDLK_BACKSPACE:
				Game::moneySpeed += 5;
				break;
			case SDLK_MINUS:
				speed--;
				transform->speed = speed;
				break;
			case SDLK_LSHIFT:
				transform->speed = speed * 2;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				transform->velocity.y = 0;
				break;
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_LEFT:
				transform->velocity.x = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_LSHIFT:
				transform->speed = speed;
				break;
			default:
				break;
			}
		}

		if (transform->velocity.x > 0)
			right = true;
		else if (transform->velocity.x < 0)
			left = true;
		else {
			right = left = false;
		}

		if (transform->velocity.y > 0)
			down = true;
		else if (transform->velocity.y < 0)
			up = true;
		else {
			down = up = false;
		}

		if (right)
			if (up) {
				*angle = -45.0f;

			}
			else if (down)
				*angle = 45.0f;
			else
				*angle = 0.0f;
		else
			if (left)
				if (up)
					*angle = -135.0f;
				else if (down)
					*angle = 135.0f;
				else
					*angle = 180.0f;
			else
				if (up)
					*angle = -90;
				else
					if (down)
						*angle = 90;

	}

	private:
		float * angle;
		bool right = false;
		bool left = false;
		bool up = false;
		bool down = false;
};

