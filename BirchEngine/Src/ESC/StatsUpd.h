#pragma once

#include "ESC.h"
#include "Components.h"
#include "../Game.h"
#include <sstream>

class LabUpd : public Component
{
public:
	LabUpd(Entity * l1, Entity * l2, Entity * l3, Entity * l4) : healthLabel(l1), moneyLabel(l2), expLabel(l3), monneypers(l4){}
	~LabUpd(){}

	void update() override {
		int delay = static_cast<int>((SDL_GetTicks() / 31) % 2);
		if (prevTime != delay) {
			Game::money += (float)Game::moneySpeed / 32;
			prevTime = delay;
		}

		std::stringstream sh;
		sh << "HEALTH: " << Game::health;
		healthLabel->getComponent<UILabel>().SetLabelText(sh.str());
		healthLabel->getComponent<UILabel>().upd();
		std::stringstream sm;
		sm << "MONEY: " << (int)Game::money << "$";
		moneyLabel->getComponent<UILabel>().SetLabelText(sm.str());
		moneyLabel->getComponent<UILabel>().upd();
		std::stringstream se;
		se << "EXP: " << Game::exp << "#";
		expLabel->getComponent<UILabel>().SetLabelText(se.str());
		expLabel->getComponent<UILabel>().upd();
		std::stringstream ss;
		ss << "money income: " << Game::moneySpeed << "m/s";
		monneypers->getComponent<UILabel>().SetLabelText(ss.str());
		monneypers->getComponent<UILabel>().upd();
	}

private:
	int prevTime = 0;
	Entity * moneyLabel;
	Entity * healthLabel;
	Entity * expLabel;
	Entity * monneypers;
};
