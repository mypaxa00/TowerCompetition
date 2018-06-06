#pragma once

#include <SDL.h>
#include "../Game.h"
#include "../AssetManager.h"
#include "Components.h"

const int LEFT_SPACE = 100;
const int BETWEEN_SPACE = 10;
const int TILE_SIZE = 64;
const int BUTTON_H = 20;
const int BUTTON_W = 160;
const int MAIN_B_W = 140;
const int MAIN_B_H = 45;

class UpgradingMenue : public Component
{
public:
	UpgradingMenue(Manager * man) : manager(man) {}
	~UpgradingMenue() {}

	void init() override {
		SDL_Color color = { 255, 255, 255, 255 };
		mainButton = Game::assets->CreateButton(LEFT_SPACE + TILE_SIZE, 0, MAIN_B_W, MAIN_B_H, "     SHOW");
		menuegroup = &manager->getGroup(Game::G_UpgradeMenue);
		BackgroundPlate = Game::assets->CreateBGPanel(LEFT_SPACE, -1 * (MAIN_B_H + 3 * BETWEEN_SPACE + 2 * TILE_SIZE),
			TILE_SIZE + 3 * BETWEEN_SPACE + BUTTON_W, MAIN_B_H + 3 * BETWEEN_SPACE + 2 * TILE_SIZE, AssetManager::B_Blue);
		BackgroundPlate->addGroup(Game::G_UpgradeMenue);		

		soldier = &manager->addEntity();
		soldier->addComponent<TransformComponent>(LEFT_SPACE + BETWEEN_SPACE, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE));
		soldier->addComponent<SpriteComponent>("soldier1");
		soldier->addGroup(Game::G_Labels);
		soldier->addGroup(Game::G_UpgradeMenue);
		if (Game::money >= 50) {
			SBuy = AssetManager::B_Green;
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, SBuy);
		}
		else {
			SBuy = AssetManager::B_Red;
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, SBuy);
		}
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1 * (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "50$", "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);
		if (Game::exp >= 50) {
			SUpg = AssetManager::B_Green;
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1 * (3 * BETWEEN_SPACE + 3 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 50#", SUpg, "$");
		}
		else {
			SUpg = AssetManager::B_Red;
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1 * (3 * BETWEEN_SPACE + 3 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 50#", SUpg, "$");
		}
		SButton->addGroup(Game::G_UpgradeMenue);
		SDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1 * (4 * BETWEEN_SPACE + 4 * BUTTON_H), "HP 100, S 30", color, "$");

		color = { 0, 0, 0, 255 };
		plane = &manager->addEntity();
		plane->addComponent<TransformComponent>(LEFT_SPACE + BETWEEN_SPACE, -1 * (BETWEEN_SPACE + TILE_SIZE));
		if (Game::exp >= 100) {
			color = { 0, 77, 0, 255 }; //tree green
			PUpg = AssetManager::B_Green;
			PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1 * (BETWEEN_SPACE + BUTTON_H),
				BUTTON_W, BUTTON_H, "Unlock: 100#", PUpg, "$");
		}
		else {
			PUpg = AssetManager::B_Red;
			PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1 * (BETWEEN_SPACE + BUTTON_H),
				BUTTON_W, BUTTON_H, "Unlock: 100#", PUpg, "$");
		}
		PButton->addGroup(Game::G_UpgradeMenue);
		planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1 * (BETWEEN_SPACE + TILE_SIZE),
			TILE_SIZE, TILE_SIZE, AssetManager::B_White);
		planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE * 2, -1 * (BETWEEN_SPACE + TILE_SIZE / 1.5),
			"Lock", "Blocks", color);
		planeBG->addGroup(Game::G_UpgradeMenue);
		color = { 128, 128, 128, 255 }; //light gray
		PDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1 * (2 * BETWEEN_SPACE + 2 * BUTTON_H), "No info", color, "$");

	}

	void update() override {
		if (mainButton->getComponent<MouseButtonComponent>().pressed1 || (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_BACKQUOTE)) {
			if (!menue && !roll) {
				roll = true;
				mainButton->getComponent<UILabel>().SetLabelText("     HIDE");
			}
			else {
				roll_back = true;
				mainButton->getComponent<UILabel>().SetLabelText("     SHOW");
			}
		}

		if (roll) {
			for (Entity * m : *menuegroup) {
				m->getComponent<TransformComponent>().position.y += 5;
			}
			for (Entity * m : *menuegroup) {
				if(m->hasComponent<UILabel>())
				m->getComponent<UILabel>().position.y += 5;
			}
			Vector2D pos = SDescription->getComponent<UILabel>().pos();
			SDescription->getComponent<UILabel>().SetLabelPos(pos.x, pos.y += 5);
			pos = PDescription->getComponent<UILabel>().pos();
			PDescription->getComponent<UILabel>().SetLabelPos(pos.x, pos.y += 5);
			if (BackgroundPlate->getComponent<TransformComponent>().position.y > -5) {
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
			Vector2D pos = SDescription->getComponent<UILabel>().pos();
			SDescription->getComponent<UILabel>().SetLabelPos(pos.x, pos.y -= 5);
			pos = PDescription->getComponent<UILabel>().pos();
			PDescription->getComponent<UILabel>().SetLabelPos(pos.x, pos.y -= 5);
			if (BackgroundPlate->getComponent<TransformComponent>().height + BackgroundPlate->getComponent<TransformComponent>().position.y < 0) {
				roll_back = false;
				menue = false;
				return;
			}
		}

		chekMenue();
	}

private:
	Manager * manager;

	Entity * BackgroundPlate;
	Entity * label;
	Entity * mainButton;

	std::vector<Entity*>* menuegroup;

	bool menue = false;

	bool roll = false;
	bool roll_back = false;

	Entity * soldier;
	Entity * SButton;
	Entity * SDescription;
	Entity * soldierBG;
	AssetManager::ButtonColor SBuy;
	AssetManager::ButtonColor SUpg;
	int soldierLvl = 1;

	Entity * plane;
	Entity * PButton;
	Entity * PDescription;
	Entity * planeBG;
	AssetManager::ButtonColor PBuy;
	AssetManager::ButtonColor PUpg;
	int planeLvl = 0;

	void chekMenue() {
		if (menue) {
			switch (planeLvl)
			{
			case 0: {
				if (Game::exp >= 100) {
					if (PUpg != AssetManager::B_Green) {
						PButton->destroy();
						PUpg = AssetManager::B_Green;
						PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BUTTON_H + 4 * BETWEEN_SPACE, BUTTON_W, BUTTON_H, "Unlock: 100#", PUpg, "$");
						PButton->addGroup(Game::G_UpgradeMenue);
					}
					if (PButton->getComponent<MouseButtonComponent>().see) {
						SDL_Color color = { 148, 0, 211, 255 };
						PDescription->getComponent<UILabel>().SetLabelText("HP 90, S 60", "$", color);
						if (PButton->getComponent<MouseButtonComponent>().pressed1) {
							SDL_Color color = { 255, 255, 255, 255 };
							PDescription->getComponent<UILabel>().SetLabelText("HP 90, S 60", "$", color);
							planeLvl++;
							Game::exp -= 100;
							planeBG->getComponent<UILabel>().SetLabelText("100$");
							planeBG->getComponent<UILabel>().SetLabelPos(LEFT_SPACE + BETWEEN_SPACE + 3, 2 * BETWEEN_SPACE + TILE_SIZE + MAIN_B_H + 3);
							plane->getComponent<SpriteComponent>().setTex("plane1");
							return;
						}
					}
					else {
						SDL_Color color = { 128, 128, 128, 255 };
						PDescription->getComponent<UILabel>().SetLabelText("No info", "$", color);
					}
				}
				else {
					if (PUpg != AssetManager::B_Red) {
						PButton->destroy();
						PUpg = AssetManager::B_Red;
						PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BUTTON_H + 4 * BETWEEN_SPACE, BUTTON_W, BUTTON_H, "Unlock: 100#", PUpg, "$");
						PButton->addGroup(Game::G_UpgradeMenue);
					}
				}
				break; }
			case 1: {
				if (Game::exp >= 200) {
					if (PUpg != AssetManager::B_Green) {
						PButton->destroy();
						PUpg = AssetManager::B_Green;
						PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BUTTON_H + 4 * BETWEEN_SPACE, BUTTON_W, BUTTON_H, "Unlock: 200#", PUpg, "$");
						PButton->addGroup(Game::G_UpgradeMenue);
					}
					if (PButton->getComponent<MouseButtonComponent>().see) {
						SDL_Color color = { 148, 0, 211, 255 };
						PDescription->getComponent<UILabel>().SetLabelText("HP 100, S 80", "$", color);
						if (PButton->getComponent<MouseButtonComponent>().pressed1) {
							SDL_Color color = { 255, 255, 255, 255 };
							PDescription->getComponent<UILabel>().SetLabelText("HP 100, S 80", "$", color);
							planeLvl++;
							Game::exp -= 200;
							planeBG->getComponent<UILabel>().SetLabelText("200$");
							plane->getComponent<SpriteComponent>().setTex("plane2");
							return;
						}
					}
					else {
						SDL_Color color = { 225, 225, 225, 255 };
						PDescription->getComponent<UILabel>().SetLabelText("HP 90, S 60", "$", color);
					}
				}
				else {
					if (PUpg != AssetManager::B_Red) {
						PButton->destroy();
						PUpg = AssetManager::B_Red;
						PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BUTTON_H + 4 * BETWEEN_SPACE, BUTTON_W, BUTTON_H, "Unlock: 200#", PUpg, "$");
						PButton->addGroup(Game::G_UpgradeMenue);
					}
				}
				if (Game::money >= 100) {
					if (PBuy != AssetManager::B_Green) {
						planeBG->destroy();
						PBuy = AssetManager::B_Green;
						planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE,
							TILE_SIZE, TILE_SIZE, PBuy);
						planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE + 3, "100$", "$");
						planeBG->addComponent<MouseButtonComponent>();
						planeBG->addGroup(Game::G_UpgradeMenue);
					}
					if (PButton->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Plane1);
						Game::money -= 100;
					}
				}
				else {
					if (PBuy != AssetManager::B_Red) {
						PButton->destroy();
						PBuy = AssetManager::B_Red;
						planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE,
							TILE_SIZE, TILE_SIZE, PBuy);
						planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE + 3, "100$", "$");
						planeBG->addComponent<MouseButtonComponent>();
						planeBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break; }
			case 2: {
				if (Game::money >= 200) {
					if (PBuy != AssetManager::B_Green) {
						planeBG->destroy();
						PBuy = AssetManager::B_Green;
						planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE,
							TILE_SIZE, TILE_SIZE, PBuy);
						planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE + 3, "200", "$");
						planeBG->addComponent<MouseButtonComponent>();
						planeBG->addGroup(Game::G_UpgradeMenue);
					}
					if (PButton->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Plane2);
						Game::money -= 200;
					}
				}
				else {
					if (PBuy != AssetManager::B_Red) {
						PButton->destroy();
						PBuy = AssetManager::B_Red;
						planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE,
							TILE_SIZE, TILE_SIZE, PBuy);
						planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 2 * BETWEEN_SPACE + TILE_SIZE + 3, "200$", "$");
						planeBG->addComponent<MouseButtonComponent>();
						planeBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break; }
			}
			switch (soldierLvl)
			{
			case 1: {
				if (Game::exp >= 50) {
					if (SUpg != AssetManager::B_Green) {
						SButton->destroy();
						SUpg = AssetManager::B_Green;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 2 * BETWEEN_SPACE + BUTTON_H,
							BUTTON_W, BUTTON_H, "Upgrade: 50#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
					if (SButton->getComponent<MouseButtonComponent>().see) {
						SDL_Color color = { 148, 0, 211, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 110, S 40", "$", color);
						if (SButton->getComponent<MouseButtonComponent>().pressed1) {
							soldierLvl++;
							Game::exp -= 50;
							soldierBG->getComponent<UILabel>().SetLabelText("60$");
							soldier->getComponent<SpriteComponent>().setTex("soldier2");
							return;
						}
					}
					else {
						SDL_Color color = { 255, 255, 255, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 100, S 30", "Blocks", color);
					}
				}
				else {
					if (SUpg != AssetManager::B_Red) {
						SButton->destroy();
						SUpg = AssetManager::B_Red;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 2 * BETWEEN_SPACE + BUTTON_H,
							BUTTON_W, BUTTON_H, "Upgrade: 50#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
				}
				if (Game::money >= 50) {
					if (SBuy != AssetManager::B_Green) {
						soldierBG->destroy();
						SBuy = AssetManager::B_Green;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + BETWEEN_SPACE, TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + BETWEEN_SPACE + TILE_SIZE + 3, "50$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
					if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Soldier1);
						Game::money -= 50;
					}
				}
				else {
					if (SBuy != AssetManager::B_Red) {
						soldierBG->destroy();
						SBuy = AssetManager::B_Red;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + BETWEEN_SPACE, TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + BETWEEN_SPACE + TILE_SIZE + 3, "50$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break;
			}
			case 2: {
				if (Game::exp >= 60) {
					if (SUpg != AssetManager::B_Green) {
						SButton->delGroup(Game::G_UpgradeMenue);
						SButton->delGroup(Game::G_Buttons);
						SButton->destroy();
						SButton = NULL;
						SUpg = AssetManager::B_Green;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (3 * BETWEEN_SPACE + 3 * BUTTON_H),
							BUTTON_W, BUTTON_H, "Upgrade: 60#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
					if (SButton->getComponent<MouseButtonComponent>().see) {
						SDL_Color color = { 148, 0, 211, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 125, S 50", "Blocks", color);
						if (SButton->getComponent<MouseButtonComponent>().pressed1) {
							soldierLvl++;
							Game::exp -= 60;
							soldierBG->getComponent<UILabel>().SetLabelText("75$");
							soldier->getComponent<SpriteComponent>().setTex("soldier3");
							return;
						}
					}
					else {
						SDL_Color color = { 255, 255, 255, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 110, S 40", "Blocks", color);
					}
				}
				else {
					if (SUpg != AssetManager::B_Red) {
						SButton->delGroup(Game::G_UpgradeMenue);
						SButton->delGroup(Game::G_Buttons);
						SButton->destroy();
						SButton = NULL;
						SUpg = AssetManager::B_Red;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (3 * BETWEEN_SPACE + 3 * BUTTON_H),
							BUTTON_W, BUTTON_H, "Upgrade: 60#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
				}
				if (Game::money >= 60) {
					if (SBuy != AssetManager::B_Green) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Green;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "60$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
					if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Soldier2);
						Game::money -= 60;
					}
				}
				else {
					if (SBuy != AssetManager::B_Red) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Red;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "60$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break;
			}
			case 3: {
				if (Game::exp >= 75) {
					if (SUpg != AssetManager::B_Green) {
						SButton->delGroup(Game::G_UpgradeMenue);
						SButton->delGroup(Game::G_Buttons);
						SButton->destroy();
						SButton = NULL;
						SUpg = AssetManager::B_Green;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (3 * BETWEEN_SPACE + 3 * BUTTON_H),
							BUTTON_W, BUTTON_H, "Upgrade: 75#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
					if (SButton->getComponent<MouseButtonComponent>().see) {
						SDL_Color color = { 148, 0, 211, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 150, S 60", "Blocks", color);
						if (SButton->getComponent<MouseButtonComponent>().pressed1) {
							soldierLvl++;
							Game::exp -= 75;
							soldierBG->getComponent<UILabel>().SetLabelText("100$");
							soldier->getComponent<SpriteComponent>().setTex("soldier4");
							return;
						}
					}
					else {
						SDL_Color color = { 255, 255, 255, 255 };
						SDescription->getComponent<UILabel>().SetLabelText("HP 125, S 50", "Blocks", color);
					}
				}
				else {
					if (SUpg != AssetManager::B_Red) {
						SButton->delGroup(Game::G_UpgradeMenue);
						SButton->delGroup(Game::G_Buttons);
						SButton->destroy();
						SButton = NULL;
						SUpg = AssetManager::B_Red;
						SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (3 * BETWEEN_SPACE + 3 * BUTTON_H),
							BUTTON_W, BUTTON_H, "Upgrade: 75#", SUpg, "$");
						SButton->addGroup(Game::G_UpgradeMenue);
					}
				}
				if (Game::money >= 75) {
					if (SBuy != AssetManager::B_Green) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Green;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "75$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
					if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Soldier3);
						Game::money -= 75;
					}
				}
				else {
					if (SBuy != AssetManager::B_Red) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Red;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "75$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break;
			}
			case 4: {
				if (Game::money >= 100) {
					if (SBuy != AssetManager::B_Green) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Green;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "100$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
					if (soldierBG->getComponent<MouseButtonComponent>().pressed1) {
						Game::assets->CreateEnemy(AssetManager::E_Soldier4);
						Game::money -= 100;
					}
				}
				else {
					if (SBuy != AssetManager::B_Red) {
						soldierBG->delGroup(Game::G_UpgradeMenue);
						soldierBG->delGroup(Game::G_BGs);
						soldierBG->destroy();
						soldierBG = NULL;
						SBuy = AssetManager::B_Red;
						soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
							TILE_SIZE, TILE_SIZE, SBuy);
						soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3,
							MAIN_B_H + 3 * BETWEEN_SPACE + 2 * BUTTON_H -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "100$", "$");
						soldierBG->addComponent<MouseButtonComponent>();
						soldierBG->addGroup(Game::G_UpgradeMenue);
					}
				}
				break;
			}
			default:
				break;
			}
		}
		return;
	}

	void chekP0() {
		SDL_Color color = { 255, 0, 0, 255 };//black
		

		

		
		//PDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}
	void chekP1() {
		if (Game::money >= 100) {
			PBuy = AssetManager::B_Green;
			planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (BETWEEN_SPACE + TILE_SIZE),
				TILE_SIZE, TILE_SIZE, PBuy);
		}
		else {
			PBuy = AssetManager::B_Red;
			planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (BETWEEN_SPACE + TILE_SIZE),
				TILE_SIZE, TILE_SIZE, PBuy);
		}
		planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1* (BETWEEN_SPACE + TILE_SIZE) + 3, "100$", "$");
		planeBG->addComponent<MouseButtonComponent>();
		planeBG->addGroup(Game::G_UpgradeMenue);

		plane->addComponent<SpriteComponent>("plane1");
		plane->addGroup(Game::G_Labels);
		plane->addGroup(Game::G_UpgradeMenue);

		if (Game::exp >= 200) {
			PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1* (BETWEEN_SPACE + BUTTON_H),
				BUTTON_W, BUTTON_H, "Upgrade: 200#", AssetManager::B_Green, "$");
		}
		else {
			PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1* (BETWEEN_SPACE + BUTTON_H),
				BUTTON_W, BUTTON_H, "Upgrade: 200#", AssetManager::B_Red, "$");
		}
		PButton->addGroup(Game::G_UpgradeMenue);

		PDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1* (2 * BETWEEN_SPACE + 2 * BUTTON_H), "HP 90, S 60");
		//PDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}
	void chekP2() {
		SDL_Color color = { 255, 215, 0, 255 };
		if (Game::money >= 200) {
			planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (BETWEEN_SPACE + TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Green);
		}
		else {
			planeBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (BETWEEN_SPACE + TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Red);
		}
		planeBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1* (BETWEEN_SPACE + TILE_SIZE) + 3, "200$", "$");
		planeBG->addComponent<MouseButtonComponent>();
		planeBG->addGroup(Game::G_UpgradeMenue);

		plane->addComponent<SpriteComponent>("plane2");
		plane->addGroup(Game::G_Labels);
		plane->addGroup(Game::G_UpgradeMenue);

		PButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1* (BETWEEN_SPACE + BUTTON_H),
			BUTTON_W, BUTTON_H, "MAX LEVEL", AssetManager::B_Yellow, "$");
		PButton->addGroup(Game::G_UpgradeMenue);

		PDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1* (2 * BETWEEN_SPACE + 2 * BUTTON_H), "HP 100, S 80", color);
		//PDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}

	void chekS2() {
		if (Game::money >= 60) {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Green);
		}
		else {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Red);
		}
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "60$", "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);

		soldier->addComponent<SpriteComponent>("soldier2");
		soldier->addGroup(Game::G_Labels);
		soldier->addGroup(Game::G_UpgradeMenue);

		if (Game::exp >= 75) {
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1* (3 * BETWEEN_SPACE + 3 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 60#", AssetManager::B_Green, "$");
		}
		else {
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1* (2 * BETWEEN_SPACE + 2 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 60#", AssetManager::B_Red, "$");
		}
		SButton->addGroup(Game::G_UpgradeMenue);

		SDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1* (4 * BETWEEN_SPACE + 4 * BUTTON_H), "HP 110, S 40");
		//SDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}
	void chekS3() {
		if (Game::money >= 75) {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Green);
		}
		else {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Red);
		}
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "75$", "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);

		soldier->addComponent<SpriteComponent>("soldier3");
		soldier->addGroup(Game::G_Labels);
		soldier->addGroup(Game::G_UpgradeMenue);

		if (Game::exp >= 75) {
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1* (3 * BETWEEN_SPACE + 3 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 75#", AssetManager::B_Green, "$");
		}
		else {
			SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
				-1* (2 * BETWEEN_SPACE + 2 * BUTTON_H), BUTTON_W, BUTTON_H, "Upgrade: 75#", AssetManager::B_Red, "$");
		}
		SButton->addGroup(Game::G_UpgradeMenue);

		SDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE), -1* (4 * BETWEEN_SPACE + 4 * BUTTON_H), "HP 125, S 50");
		//SDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}
	void chekS4() {
		SDL_Color color = { 255, 215, 0, 255 };
		if (Game::money >= 100) {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Green);
		}
		else {
			soldierBG = Game::assets->CreateBGPanel(LEFT_SPACE + BETWEEN_SPACE, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE),
				TILE_SIZE, TILE_SIZE, AssetManager::B_Red);
		}
		soldierBG->addComponent<UILabel>(LEFT_SPACE + BETWEEN_SPACE + 3, -1* (2 * BETWEEN_SPACE + 2 * TILE_SIZE) + 3, "100$", "$");
		soldierBG->addComponent<MouseButtonComponent>();
		soldierBG->addGroup(Game::G_UpgradeMenue);

		soldier->addComponent<SpriteComponent>("soldier4");
		soldier->addGroup(Game::G_Labels);
		soldier->addGroup(Game::G_UpgradeMenue);

		SButton = Game::assets->CreateButton((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1* (3 * BETWEEN_SPACE + 3 * BUTTON_H), BUTTON_W, BUTTON_H, "MAX LEVEL", AssetManager::B_Yellow, "$");

		SButton->addGroup(Game::G_UpgradeMenue);

		SDescription = Game::assets->CreateLabel((2 * BETWEEN_SPACE + LEFT_SPACE + TILE_SIZE),
			-1* (4 * BETWEEN_SPACE + 4 * BUTTON_H), "HP 150, S 60", color);
		//SDescription->addGroup(Game::G_UpgradeMenue);
		return;
	}
};