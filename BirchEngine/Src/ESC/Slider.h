#pragma once

#include "../AssetManager.h"
#include "../Game.h"
#include <SDL.h>
#include "Components.h";

class Slider : public Component
{
public:
	int value;
	bool changed;
	bool hold = false;

	Slider(Entity * bg, int maxV, int minV, int w, AssetManager::ButtonColor c) : bg(bg), max(maxV), min(minV), width(w), color(c){}
	~Slider() { bg->destroy(); }

	void init() override {
		width -= 36;
		switch (color)
		{
		case AssetManager::B_Blue:
			entity->addComponent<SpriteComponent>("blue_circle", NULL, Vector2D(36, 36));
			break;
		case AssetManager::B_Green:
			entity->addComponent<SpriteComponent>("green_circle", NULL, Vector2D(36, 36));
			break;
		case AssetManager::B_Red:
			entity->addComponent<SpriteComponent>("red_circle", NULL, Vector2D(36, 36));
			break;
		case AssetManager::B_White:
			entity->addComponent<SpriteComponent>("white_circle", NULL, Vector2D(36, 36));
			break;
		case AssetManager::B_Yellow:
			entity->addComponent<SpriteComponent>("yellow_circle", NULL, Vector2D(36, 36));
			break;
		}
		pos = &entity->getComponent<TransformComponent>().position;
		defPos = *pos;
		entity->addGroup(Game::G_Labels);
	}

	void update() override {
		changed = false;
		switch (Game::event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (!hold && Game::event.button.button == SDL_BUTTON_LEFT) {
				int x = Game::event.button.x;
				int y = Game::event.button.y;
				if (x > pos->x && y > pos->y && x < pos->x + 36 && y < pos->y + 36) {
					hold = true;
					mouseHold = x - pos->x;
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (hold && Game::event.button.button == SDL_BUTTON_LEFT) {
				changed = true;
				hold = false;
			}
			break;
		}

		if (hold) {
			pos->x = Game::event.button.x - mouseHold;
			if (pos->x > defPos.x + width)
				pos->x = defPos.x + width;
			if (pos->x < defPos.x)
				pos->x = defPos.x;
			value = min + (max - min) * ((pos->x - defPos.x) / width);
		}
	}

private:
	int max;
	int min;
	int width;
	Vector2D * pos;
	Vector2D defPos;
	int mouseHold;
	AssetManager::ButtonColor color;
	Entity * bg;
};
