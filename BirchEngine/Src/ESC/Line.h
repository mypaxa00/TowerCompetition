#pragma once

#include "ESC.h"
#include "Components.h"
#include "../Vector2D.h"
#include <sstream>

class LineComponent : public Component
{
public:
	LineComponent(Manager * man) : manager(man)
	{}
	~LineComponent() {}
	int length = 0;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		startPos = transform->position;
		label = &manager->addEntity();
		pos = &manager->addEntity();
		SDL_Color white = { 255, 255, 255, 255 };
		label->addComponent<UILabel>(10, 65, "", "Future", white);
		pos->addComponent<UILabel>(10, 10, "", "Future", white);
		label->addGroup(Game::G_Labels);
		pos->addGroup(Game::G_Labels);
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_SPACE:
				startPos = transform->position;
				break;
			default:
				break;
			}
		}
		curPos = &transform->position;
		*curPos -= startPos;
		length = sqrt(pow(curPos->x, 2) + pow(curPos->y, 2));

		std::stringstream ssl;
		ssl << "Length = " << length;
		label->getComponent<UILabel>().SetLabelText(ssl.str());

		std::stringstream ssp;
		ssp << "pos = " << *curPos;
		pos->getComponent<UILabel>().SetLabelText(ssp.str());
	}

private:
	Manager * manager;
	TransformComponent * transform;
	Vector2D startPos;
	Vector2D * curPos;
	Entity * label;
	Entity * pos;
	
};