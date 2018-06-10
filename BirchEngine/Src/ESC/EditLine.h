#pragma once


#include "../AssetManager.h"
#include "../Game.h"
#include <SDL.h>
#include "Components.h";
#include <sstream>

class EditLine : public Component
{
public:
	std::string text = "";
	bool textChanged = false;

	EditLine(Vector2D position, Vector2D sz, int max, AssetManager::ButtonColor c = AssetManager::B_White) : pos(position), size(sz), maxSize(max), color(c){}
	~EditLine(){}

	void init() override {
		entity->addComponent<MouseButtonComponent>();
		mouse = &entity->getComponent<MouseButtonComponent>();
		SDL_Color color = { 105,105,105,255 };
		entity->addComponent<UILabel>(pos.x + 8, pos.y, "", "Future", color);
	}

	void update() override {
		if (textChanged) {
			textChanged = false;
			label = text;
			entity->getComponent<UILabel>().SetLabelText(label);
			entity->getComponent<UILabel>().upd();
		}
		if (mouse->selected) {
			set = true;
			int spawnDelay = static_cast<int>((SDL_GetTicks() / delay) % 2);
			if (prevSpawnTime != spawnDelay) {
				if (symb) {
					symb = false;
					label = text + "|";
				}
				else {
					symb = true;
					label = text;
				}
				entity->getComponent<UILabel>().SetLabelText(label);
				entity->getComponent<UILabel>().upd();
				prevSpawnTime = spawnDelay;
			}
			if (Game::event.type == SDL_KEYDOWN) {
				if (!pressed) {
					if(Game::event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
						text.pop_back();
						textChanged = true;
					}

					if (text.length() < maxSize) {
						switch (Game::event.key.keysym.sym)
						{
						
						case SDLK_1:
							text.push_back('1');
							textChanged = true;
							break;
						case SDLK_2:
							text.push_back('2');
							textChanged = true;
							break;
						case SDLK_3:
							text.push_back('3');
							textChanged = true;
							break;
						case SDLK_4:
							text.push_back('4');
							textChanged = true;
							break;
						case SDLK_5:
							text.push_back('5');
							textChanged = true;
							break;
						case SDLK_6:
							text.push_back('6');
							textChanged = true;
							break;
						case SDLK_7:
							text.push_back('7');
							textChanged = true;
							break;
						case SDLK_8:
							text.push_back('8');
							textChanged = true;
							break;
						case SDLK_9:
							text.push_back('9');
							textChanged = true;
							break;
						case SDLK_0:
							text.push_back('0');
							textChanged = true;
							break;
						case SDLK_KP_1:
							text.push_back('1');
							textChanged = true;
							break;
						case SDLK_KP_2:
							text.push_back('2');
							textChanged = true;
							break;
						case SDLK_KP_3:
							text.push_back('3');
							textChanged = true;
							break;
						case SDLK_KP_4:
							text.push_back('4');
							textChanged = true;
							break;
						case SDLK_KP_5:
							text.push_back('5');
							textChanged = true;
							break;
						case SDLK_KP_6:
							text.push_back('6');
							textChanged = true;
							break;
						case SDLK_KP_7:
							text.push_back('7');
							textChanged = true;
							break;
						case SDLK_KP_8:
							text.push_back('8');
							textChanged = true;
							break;
						case SDLK_KP_9:
							text.push_back('9');
							textChanged = true;
							break;
						case SDLK_KP_0:
							if (DotAllowed) {
								text.push_back('.');
								textChanged = true;
							}
							break;
						case SDLK_PERIOD:
							if (DotAllowed) {
								text.push_back('.');
								textChanged = true;
							}
							break;
						case SDLK_KP_D:
							if (DotAllowed) {
								text.push_back('.');
								textChanged = true;
							}
							break;
						case SDLK_KP_PERIOD:
							if (DotAllowed) {
								text.push_back('.');
								textChanged = true;
							}
							break;
						}
					}
					pressed = true;
				}
			}
			
			if(Game::event.type == SDL_KEYUP)
			{
				pressed = false;
			}
		} else {
			if (!set) {
				entity->getComponent<UILabel>().SetLabelText(text);
				entity->getComponent<UILabel>().upd();
				set = true;
			}
		}
	}

	void AllowLetters() {
		LettersAlloved = true;
	}
	void AllowDot() {
		DotAllowed = true;
	}

private:
	Vector2D pos;
	Vector2D size;
	MouseButtonComponent * mouse;
	Entity * selection;
	std::string label;

	int maxSize;
	AssetManager::ButtonColor color;
	bool LettersAlloved = false;
	bool DotAllowed = false;
	bool pressed = false;
	bool symb = false;
	bool set = false;


	int prevSpawnTime = 0;
	const int delay = 500;
};
