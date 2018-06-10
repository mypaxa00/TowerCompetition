#pragma once

#include <SDL.h>
#include "../Game.h"
#include "../AssetManager.h"
#include "Components.h"
#include <math.h>
#include <sstream>

const int BETWEEN_SPACE = 10;
const int TILE_SIZE = 64;
const int BUTTON_H = 20;
const int BUTTON_W = 160;
const int MAIN_B_W = 130;
const int MAIN_B_H = 45;
const int MONEY_B_W = BETWEEN_SPACE + TILE_SIZE + BUTTON_W;

class UpgradingMenue : public Component
{
public:
	/*
		POS - (0-1676)
	*/
	UpgradingMenue(Manager * man, int POS = 0) : manager(man), LEFT_SPACE(POS) {}
	~UpgradingMenue() {}

	void init() override {
		SDL_Color color = { 255, 255, 255, 255 };
		mainButton = Game::assets->CreateButton(LEFT_SPACE + TILE_SIZE, 0, MAIN_B_W, MAIN_B_H, "     SHOP", AssetManager::B_Yellow);
		mainButton->delGroup(Game::G_Buttons);
		mainButton->addGroup(Game::G_Labels);
		menuegroup = &manager->getGroup(Game::G_UpgradeMenue);
		BackgroundPlate = Game::assets->CreateBGPanel(LEFT_SPACE, -1 * (MAIN_B_H + 4 * BETWEEN_SPACE + 2 * TILE_SIZE + BUTTON_H),
			TILE_SIZE + 3 * BETWEEN_SPACE + BUTTON_W, MAIN_B_H + 4 * BETWEEN_SPACE + 2 * TILE_SIZE + BUTTON_H, AssetManager::B_Blue);
		BackgroundPlate->addGroup(Game::G_UpgradeMenue);
		
		if (Game::exp >= 100)
			MUpg = AssetManager::B_Green;
		else
			MUpg = AssetManager::B_Red;
		moneyButton = Game::assets->CreateButton(LEFT_SPACE + BETWEEN_SPACE, -1 * (BETWEEN_SPACE * 3 + TILE_SIZE * 2 + BUTTON_H),
			MONEY_B_W, BUTTON_H, "money/s + 5: 100#", MUpg, "$");
		moneyButton->addGroup(Game::G_UpgradeMenue);

		soldier = &manager->addEntity();
		soldier->addComponent<TransformComponent>(LEFT_SPACE + BETWEEN_SPACE, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE));
		soldier->addComponent<SpriteComponent>("soldier1");
		soldier->addGroup(Game::G_Buttons);
		soldier->addGroup(Game::G_UpgradeMenue);
		if (Game::money >= 50)
			SBuy = AssetManager::B_Green;
		else
			SBuy = AssetManager::B_Red;
		soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
			TILE_SIZE, TILE_SIZE, SBuy);
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "50$", "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);
		if (Game::exp >= 50)
			SUpg = AssetManager::B_Green;
		else
			SUpg = AssetManager::B_Red;
		SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1 * (2 * BETWEEN_SPACE + TILE_SIZE + BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 50#", SUpg, "$");
		SButton->addGroup(Game::G_UpgradeMenue);
		SDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1 * (3 * BETWEEN_SPACE + 2 * BUTTON_H + TILE_SIZE), "HP 100, S 30", color, "$");
		SDescription->delGroup(Game::G_Labels);
		SDescription->addGroup(Game::G_Buttons);
		sdesc = &SDescription->getComponent<UILabel>();

		plane = &manager->addEntity();
		plane->addComponent<TransformComponent>(LEFT_SPACE + BETWEEN_SPACE, -1 * (BETWEEN_SPACE + TILE_SIZE));
		plane->addGroup(Game::G_UpgradeMenue);
		if (Game::exp >= 100) {
			color = { 0, 77, 0, 255 }; //tree green
			PUpg = AssetManager::B_Green;
		}
		else {
			color = { 0, 0, 0, 255 };
			PUpg = AssetManager::B_Red;
		}
		PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1 * (BETWEEN_SPACE + BUTTON_H),
			BUTTON_W, BUTTON_H, "Unlock: 100#", PUpg, "$");
		PButton->addGroup(Game::G_UpgradeMenue);
		planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1 * (BETWEEN_SPACE + TILE_SIZE),
			TILE_SIZE, TILE_SIZE, AssetManager::B_White);
		planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE * 2, -1 * (BETWEEN_SPACE + TILE_SIZE / 1.5),
			"Lock", "Blocks", color);
		planeBG->addGroup(Game::G_UpgradeMenue);
		planeBG->addComponent<MouseButtonComponent>();
		color = { 128, 128, 128, 255 }; //light gray
		PDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1 * (2 * BETWEEN_SPACE + 2 * BUTTON_H), "No info", color, "$");
		PDescription->delGroup(Game::G_Labels);
		PDescription->addGroup(Game::G_Buttons);
		pdesc = &PDescription->getComponent<UILabel>();

	}

	void update() override {
		if (mainButton->getComponent<MouseButtonComponent>().pressed1 || (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_BACKQUOTE)) {
			if (!menue && !roll) {
				roll = true;
				mainButton->getComponent<UILabel>().SetLabelText("     HIDE");
			}
			else {
				roll_back = true;
				mainButton->getComponent<UILabel>().SetLabelText("     SHOP");
			}
		}

		if (roll) {
			for (Entity * m : *menuegroup) {
				m->getComponent<TransformComponent>().position.y += 5;
			}
			for (Entity * m : *menuegroup) {
				if (m->hasComponent<UILabel>())
					m->getComponent<UILabel>().position.y += 5;
			}
			Vector2D pos = sdesc->pos();
			sdesc->SetLabelPos(pos.x, pos.y += 5);
			sdesc->upd();
			pos = pdesc->pos();
			pdesc->SetLabelPos(pos.x, pos.y += 5);
			pdesc->upd();
			if (BackgroundPlate->getComponent<TransformComponent>().position.y > -5) {
				if (BackgroundPlate->getComponent<TransformComponent>().position.y != 0) {
					float mv = fabsf(BackgroundPlate->getComponent<TransformComponent>().position.y);
					for (Entity * m : *menuegroup) {
						m->getComponent<TransformComponent>().position.y += mv;
					}
					for (Entity * m : *menuegroup) {
						if (m->hasComponent<UILabel>())
							m->getComponent<UILabel>().position.y += mv;
					}
					Vector2D pos = sdesc->pos();
					sdesc->SetLabelPos(pos.x, pos.y += mv);
					sdesc->upd();
					pos = pdesc->pos();
					pdesc->SetLabelPos(pos.x, pos.y += mv);
					pdesc->upd();
				}
				roll = false;
				menue = true;
			}
		}

		if (roll_back) {
			for (auto& m : *menuegroup) {
				m->getComponent<TransformComponent>().position.y -= 5;
			}
			for (Entity * m : *menuegroup) {
				if (m->hasComponent<UILabel>())
					m->getComponent<UILabel>().position.y -= 5;
			}
			Vector2D pos = sdesc->pos();
			sdesc->SetLabelPos(pos.x, pos.y -= 5);
			sdesc->upd();
			pos = pdesc->pos();
			pdesc->SetLabelPos(pos.x, pos.y -= 5);
			pdesc->upd();
			if (BackgroundPlate->getComponent<TransformComponent>().height + BackgroundPlate->getComponent<TransformComponent>().position.y < 0) {
				roll_back = false;
				menue = false;
				return;
			}
		}

		if (menue) {
			chekMenue();
		}
	}

private:

	int LEFT_SPACE = 0;

	Manager * manager;

	Entity * BackgroundPlate;
	Entity * label;
	Entity * mainButton;

	std::vector<Entity*>* menuegroup;

	bool menue = false;

	bool roll = false;
	bool roll_back = false;

	Entity * moneyButton;
	int mLevel = 0;
	AssetManager::ButtonColor MUpg;

	Entity * soldier;
	Entity * SButton;
	Entity * SDescription;
	UILabel * sdesc;
	Entity * soldierBG;
	AssetManager::ButtonColor SBuy;
	AssetManager::ButtonColor SUpg;
	int soldierLvl = 1;

	Entity * plane;
	Entity * PButton;
	Entity * PDescription;
	UILabel * pdesc;
	Entity * planeBG;
	AssetManager::ButtonColor PBuy;
	AssetManager::ButtonColor PUpg;
	int planeLvl = 0;

	void updatePButton(std::string label, AssetManager::ButtonColor color) {
		PButton->destroy();
		PUpg = color;
		PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			MAIN_B_H + 3 * BETWEEN_SPACE + 2 * TILE_SIZE, BUTTON_W, BUTTON_H, label, PUpg, "$");
		PButton->addGroup(Game::G_UpgradeMenue);
	}

	void updatePlaneBG(std::string label, AssetManager::ButtonColor color) {
		planeBG->destroy();
		PBuy = color;
		planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
			MAIN_B_H + 3 * BETWEEN_SPACE + TILE_SIZE + BUTTON_H,
			TILE_SIZE, TILE_SIZE, PBuy);
		planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
			MAIN_B_H + 3 * BETWEEN_SPACE + TILE_SIZE + BUTTON_H + 3, label, "$");
		planeBG->addComponent<MouseButtonComponent>();
		planeBG->addGroup(Game::G_UpgradeMenue);
	}

	void updateSButton(std::string label, AssetManager::ButtonColor color) {
		SButton->destroy();
		SUpg = color;
		SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE,
			BUTTON_W, BUTTON_H, label, SUpg, "$");
		SButton->addGroup(Game::G_UpgradeMenue);
	}

	void updateSoldierBG(std::string label, AssetManager::ButtonColor color) {
		soldierBG->destroy();
		SBuy = color;
		soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
			MAIN_B_H + 2 * BETWEEN_SPACE + BUTTON_H, TILE_SIZE, TILE_SIZE, SBuy);
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
			MAIN_B_H + 2 * BETWEEN_SPACE + BUTTON_H + 3, label, "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);
	}

	void chekMenue() {

		if (mLevel < 5) {
			if (Game::exp >= 100 + 50 * mLevel) {
				if (MUpg != AssetManager::B_Green) {
					MUpg = AssetManager::B_Green;
					std::stringstream ss;
					ss << "money/s + 5: " << (100 + 50 * mLevel) << "#";
					moneyButton->destroy();
					moneyButton = Game::assets->CreateButton(LEFT_SPACE + BETWEEN_SPACE, MAIN_B_H + BETWEEN_SPACE,
						MONEY_B_W, BUTTON_H, ss.str(), MUpg, "$");
				}
				if (moneyButton->getComponent<MouseButtonComponent>().pressed1) {
					Game::exp -= 100 + 50 * mLevel;
					Game::moneySpeed += 5;
					mLevel++;
					MUpg = AssetManager::B_White;
				}
			}
			else
			{
				if (MUpg != AssetManager::B_Red) {
					MUpg = AssetManager::B_Red;
					std::stringstream ss;
					ss << "money/s + 5: " << (100 + 50 * mLevel) << "#";
					moneyButton->destroy();
					moneyButton = Game::assets->CreateButton(LEFT_SPACE + BETWEEN_SPACE, MAIN_B_H + BETWEEN_SPACE,
						MONEY_B_W, BUTTON_H, ss.str(), MUpg, "$");
				}
			}
		}
		else {
			if(mLevel == 5){
				mLevel++;
				MUpg = AssetManager::B_Yellow;
				moneyButton->destroy();
				moneyButton = Game::assets->CreateButton(LEFT_SPACE + BETWEEN_SPACE, MAIN_B_H + BETWEEN_SPACE,
					MONEY_B_W, MAIN_B_H, "MAX MONNEY/S", MUpg);
			}
		}

		switch (planeLvl)
		{
		case 0: {
			if (Game::exp >= 100) {
				if (PUpg != AssetManager::B_Green) {
					updatePButton("Unlock: 100#", AssetManager::B_Green);
				}
				if (PButton->getComponent<MouseButtonComponent>().see) {
					SDL_Color color = { 148, 0, 211, 255 };
					pdesc->SetLabelText("HP 90, S 60");
					pdesc->SetLabelColor(color);
					pdesc->upd();
					if (PButton->getComponent<MouseButtonComponent>().pressed1) {
						SDL_Color color = { 255, 255, 255, 255 };
						pdesc->SetLabelText("HP 90, S 60");
						pdesc->SetLabelColor(color);
						pdesc->upd();
						planeLvl++;
						Game::exp -= 100;
						planeBG->getComponent<UILabel>().SetLabelText("100$");
						plane->addComponent<SpriteComponent>("plane1");
						plane->addGroup(Game::G_Buttons);
						updatePlaneBG("100$", AssetManager::B_Green);
						updatePButton("Unlock: 200#", AssetManager::B_Green);
						return;
					}
				}
				else {
					SDL_Color color = { 255, 255, 255, 255 };
					pdesc->SetLabelText("No info");
					pdesc->SetLabelColor(color);
					pdesc->upd();
				}
			}
			else {
				if (PUpg != AssetManager::B_Red) {
					updatePButton("Unlock: 100#", AssetManager::B_Red);
				}
			}
			break; }
		case 1: {
			if (Game::exp >= 200) {
				if (PUpg != AssetManager::B_Green) {
					updatePButton("Update: 200#", AssetManager::B_Green);
				}
				if (PButton->getComponent<MouseButtonComponent>().see) {
					SDL_Color color = { 148, 0, 211, 255 };
					pdesc->SetLabelText("HP 100, S 80");
					pdesc->SetLabelColor(color);
					pdesc->upd();

					if (PButton->getComponent<MouseButtonComponent>().pressed1) {
						SDL_Color color = { 255, 255, 255, 255 };
						pdesc->SetLabelText("HP 100, S 80");
						pdesc->SetLabelColor(color);
						pdesc->upd();
						planeLvl++;
						Game::exp -= 200;
						planeBG->getComponent<UILabel>().SetLabelText("200$");
						plane->getComponent<SpriteComponent>().setTex("plane2");
						updatePlaneBG("200$", AssetManager::B_Green);
						updatePButton("MAX LEVEL", AssetManager::B_Yellow);
						return;
					}
				}
				else {
					SDL_Color color = { 255, 225, 225, 255 };
					pdesc->SetLabelText("HP 90, S 60");
					pdesc->SetLabelColor(color);
					pdesc->upd();
				}
			}
			else {
				if (PUpg != AssetManager::B_Red) {
					updatePButton("Update: 200#", AssetManager::B_Red);
				}
			}
			if (Game::money >= 100) {
				if (PBuy != AssetManager::B_Green) {
					updatePlaneBG("100$", AssetManager::B_Green);
				}
				if (planeBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Plane1);
					Game::money -= 100;
				}
			}
			else {
				if (PBuy != AssetManager::B_Red) {
					updatePlaneBG("100$", AssetManager::B_Red);
				}
			}
			break; }
		case 2: {
			if (Game::money >= 200) {
				if (PBuy != AssetManager::B_Green) {
					updatePlaneBG("200$", AssetManager::B_Green);
				}
				if (planeBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Plane2);
					Game::money -= 200;
				}
			}
			else {
				if (PBuy != AssetManager::B_Red) {
					updatePlaneBG("200$", AssetManager::B_Red);
				}
			}
			break; }
		}
		switch (soldierLvl)
		{
		case 1: {
			if (Game::exp >= 50) {
				if (SUpg != AssetManager::B_Green) {
					updateSButton("Upgrade: 50#", AssetManager::B_Green);
				}
				if (SButton->getComponent<MouseButtonComponent>().see) {
					SDL_Color color = { 148, 0, 211, 255 };
					sdesc->SetLabelText("HP 110, S 40");
					sdesc->SetLabelColor(color);
					sdesc->upd();
					if (SButton->getComponent<MouseButtonComponent>().pressed1) {
						soldierLvl++;
						Game::exp -= 50;
						soldierBG->getComponent<UILabel>().SetLabelText("60$");
						soldier->getComponent<SpriteComponent>().setTex("soldier2");
						SDL_Color color = { 255, 255, 255, 255 };
						sdesc->SetLabelText("HP 110, S 40");
						sdesc->SetLabelColor(color);
						sdesc->upd();
						updateSoldierBG("60$", AssetManager::B_Green);
						updateSButton("Upgrade: 60#", AssetManager::B_Green);
						return;
					}
				}
				else {
					SDL_Color color = { 255, 255, 255, 255 };
					sdesc->SetLabelText("HP 100, S 30");
					sdesc->SetLabelColor(color);
					sdesc->upd();
				}
			}
			else {
				if (SUpg != AssetManager::B_Red) {
					updateSButton("Upgrade: 50#", AssetManager::B_Red);
				}
			}
			if (Game::money >= 50) {
				if (SBuy != AssetManager::B_Green) {
					updateSoldierBG("50$", AssetManager::B_Green);
				}
				if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Soldier1);
					Game::money -= 50;
				}
			}
			else {
				if (SBuy != AssetManager::B_Red) {
					updateSoldierBG("50$", AssetManager::B_Red);
				}
			}
			break;
		}
		case 2: {
			if (Game::exp >= 60) {
				if (SUpg != AssetManager::B_Green) {
					updateSButton("Upgrade: 60#", AssetManager::B_Green);
				}
				if (SButton->getComponent<MouseButtonComponent>().see) {
					SDL_Color color = { 148, 0, 211, 255 };
					sdesc->SetLabelText("HP 125, S 50");
					sdesc->SetLabelColor(color);
					sdesc->upd();
					if (SButton->getComponent<MouseButtonComponent>().pressed1) {
						soldierLvl++;
						Game::exp -= 60;
						soldierBG->getComponent<UILabel>().SetLabelText("75$");
						soldier->getComponent<SpriteComponent>().setTex("soldier3");
						SDL_Color color = { 255, 255, 255, 255 };
						sdesc->SetLabelText("HP 125, S 50");
						sdesc->SetLabelColor(color);
						sdesc->upd();
						updateSoldierBG("75$", AssetManager::B_Green);
						updateSButton("Upgrade: 75#", AssetManager::B_Green);
						return;
					}
				}
				else {
					SDL_Color color = { 255, 255, 255, 255 };
					sdesc->SetLabelText("HP 110, S 40");
					sdesc->SetLabelColor(color);
					sdesc->upd();
				}
			}
			else {
				if (SUpg != AssetManager::B_Red) {
					updateSButton("Upgrade: 60#", AssetManager::B_Red);
				}
			}
			if (Game::money >= 60) {
				if (SBuy != AssetManager::B_Green) {
					updateSoldierBG("60$", AssetManager::B_Green);
				}
				if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Soldier2);
					Game::money -= 60;
				}
			}
			else {
				if (SBuy != AssetManager::B_Red) {
					updateSoldierBG("60$", AssetManager::B_Red);
				}
			}
			break;
		}
		case 3: {
			if (Game::exp >= 75) {
				if (SUpg != AssetManager::B_Green) {
					updateSButton("Upgrade: 75#", AssetManager::B_Green);
				}
				if (SButton->getComponent<MouseButtonComponent>().see) {
					SDL_Color color = { 148, 0, 211, 255 };
					sdesc->SetLabelText("HP 150, S 60");
					sdesc->SetLabelColor(color);
					sdesc->upd();
					if (SButton->getComponent<MouseButtonComponent>().pressed1) {
						soldierLvl++;
						Game::exp -= 75;
						soldierBG->getComponent<UILabel>().SetLabelText("100$");
						soldier->getComponent<SpriteComponent>().setTex("soldier4");
						SDL_Color color = { 255, 255, 255, 255 };
						sdesc->SetLabelText("HP 150, S 60");
						sdesc->SetLabelColor(color);
						sdesc->upd();
						updateSoldierBG("100$", AssetManager::B_Green);
						updateSButton("MAX LEVEL", AssetManager::B_Yellow);
						return;
					}
				}
				else {
					SDL_Color color = { 255, 255, 255, 255 };
					sdesc->SetLabelText("HP 125, S 50");
					sdesc->SetLabelColor(color);
					sdesc->upd();
				}
			}
			else {
				if (SUpg != AssetManager::B_Red) {
					updateSButton("Upgrade: 75#", AssetManager::B_Red);
				}
			}
			if (Game::money >= 75) {
				if (SBuy != AssetManager::B_Green) {
					updateSoldierBG("75$", AssetManager::B_Green);
				}
				if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Soldier3);
					Game::money -= 75;
				}
			}
			else {
				if (SBuy != AssetManager::B_Red) {
					updateSoldierBG("75$", AssetManager::B_Red);
				}
			}
			break;
		}
		case 4: {
			if (Game::money >= 100) {
				if (SBuy != AssetManager::B_Green) {
					updateSoldierBG("100$", AssetManager::B_Green);
				}
				if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
					Game::assets->CreateEnemy(AssetManager::E_Soldier4);
					Game::money -= 100;
				}
			}
			else {
				if (SBuy != AssetManager::B_Red) {
					updateSoldierBG("100$", AssetManager::B_Red);
				}
			}
			break;
		}
		default:
			break;
		}
		return;
	}
};