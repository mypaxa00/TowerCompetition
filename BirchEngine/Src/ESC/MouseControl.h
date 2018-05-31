#pragma once

#include <SDL.h>
#include "ESC.h"
#include "Components.h"
#include "../Game.h"
#include "../AssetManager.h"

class MouseButtonComponent : public Component
{
public:

	bool pressed1 = false;
	bool pressed2 = false;
	bool startPress = false;
	bool see = false;

	MouseButtonComponent(std::string pressed = "") : pressedS(pressed)
	{}
	~MouseButtonComponent() {}

	void init() override {
		pos = entity->getComponent<TransformComponent>().position;
		if (entity->hasComponent<SpriteComponent>())
			sprite = &entity->getComponent<SpriteComponent>();
		else {
			entity->addComponent<SpriteComponent>("");
			sprite = &entity->getComponent<SpriteComponent>();
		}
		defaultS = sprite->id;
		width = entity->getComponent<TransformComponent>().width;
		height = entity->getComponent<TransformComponent>().height;
	}

	void update() override {
		pressed1 = false;
		pressed2 = false;
		int x;
		int y;
		switch (Game::event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			x = Game::event.button.x;
			y = Game::event.button.y;
			if (x > pos.x && see) {
				startPress = true;
				if (pressedS != "") {
					sprite->setTex(pressedS);
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			x = Game::event.button.x;
			y = Game::event.button.y;
			if (sprite->id != defaultS)
				sprite->setTex(defaultS);
			if (startPress && see) {
				if (Game::event.button.button == SDL_BUTTON_LEFT)
					pressed1 = true;
				if (Game::event.button.button == SDL_BUTTON_RIGHT)
					pressed2 = true;
			}
			startPress = false;
			break;
		default:
			break;
		}
		if (Game::event.type == SDL_MOUSEMOTION) {
			x = Game::event.motion.x;
			y = Game::event.motion.y;
			if (x > pos.x && x < pos.x + width && y > pos.y && y < pos.y + height) {
				see = true;
			}
			else
			{
				see = false;
			}
		}
	}

private:
	SpriteComponent * sprite;
	Vector2D pos;
	int width;
	int height;
	std::string defaultS;
	std::string pressedS;

};