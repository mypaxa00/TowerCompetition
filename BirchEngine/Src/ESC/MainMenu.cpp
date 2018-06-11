/*#include "MainMenu.h"

void MainMenu::init()
{
	hud = &manager->addEntity();
	hud->addComponent<TransformComponent>(-64, 1024, 1, 2048, 56);
	hud->addComponent<SpriteComponent>("hud_bg", NULL, Vector2D(190, 49));
	hud->addGroup(Game::G_BGs);
	bg = Game::assets->CreateBGPanel(750, 400, 400, 400);
	HostGame = Game::assets->CreateButton(820, 470, 260, 50, "Host Game", AssetManager::B_Yellow, "Future");
	JoinGame = Game::assets->CreateButton(820, 540, 260, 50, " Join Game", AssetManager::B_Yellow, "Future");
	Exit = Game::assets->CreateButton(890, 610, 120, 50, " Exit", AssetManager::B_Red, "Future");
}

void MainMenu::update()
{
	if (!hostmenu && HostGame->isActive() == 1 && HostGame->getComponent<MouseButtonComponent>().pressed1) {
		HostGame->destroy();
		JoinGame->destroy();
		Exit->destroy();
		SDL_Color color = { 255, 255, 255, 255 };
		start = Game::assets->CreateButton(850, 730, 160, 50, " Host", AssetManager::B_Yellow, "Future");

		map = Game::assets->CreateLabel(880, 450, "Map 1", color, "Future");
		mapChangeL = Game::assets->CreateButton(780, 450, 80, 40, "Prev", AssetManager::B_Blue, "$1.3");
		mapChangeR = Game::assets->CreateButton(1030, 450, 80, 40, "Next", AssetManager::B_Blue, "$1.3");

		color = { 255, 215, 0, 255 }; money = Game::assets->CreateLabel(800, 520, "Money: 150$", color, "Future");
		color = { 0, 127, 255, 255 }; exp = Game::assets->CreateLabel(850, 590, "EXP: 0", color, "Future");
		color = { 240, 5, 80, 255 }; ms = Game::assets->CreateLabel(850, 660, "$/s: 0", color, "Future");
		moneySlider = Game::assets->CreateSlider(800, 570, 300, 150, 10000, AssetManager::B_Yellow);
		expSlider = Game::assets->CreateSlider(800, 640, 300, 0, 1500, AssetManager::B_Blue);
		msSlider = Game::assets->CreateSlider(800, 710, 300, 0, 100, AssetManager::B_Red);
		//Map::MapPreload();
		hostmenu = true;
	}
	if (!hostmenu && JoinGame->isActive() == 1 && JoinGame->getComponent<MouseButtonComponent>().pressed1) {
		HostGame->destroy();
		JoinGame->destroy();
		Exit->destroy();
		SDL_Color color = { 255, 255, 255, 255 };
		start = Game::assets->CreateButton(850, 730, 160, 50, " Join", AssetManager::B_Yellow, "Future");
		color = { 255, 255, 255, 255 }; IPAdrress = Game::assets->CreateLabel(800, 470, "IP Adrress", color, "Future");
		ELineIP = Game::assets->CreateEditLine(780, 530, 340, 50, 15, AssetManager::B_Yellow);
		joinmenu = true;
	}
	if (!hostmenu && Exit->isActive() == 1 && Exit->getComponent<MouseButtonComponent>().pressed1) {
		HostGame->destroy();
		JoinGame->destroy();
		bg->destroy();
		Exit->destroy();
		Game::isRunning = false;
		return;
	}
	if (hostmenu) {
		if (mapChangeL->getComponent<MouseButtonComponent>().pressed1) {
			mapNum++;
			mapNum %= 5;
			std::stringstream ss;
			ss << "Map " << mapNum + 1;
			map->getComponent<UILabel>().SetLabelText(ss.str());
			map->getComponent<UILabel>().upd();
			return;
		}
		if (mapChangeR->getComponent<MouseButtonComponent>().pressed1) {
			mapNum--;
			if (mapNum < 0)
				mapNum += 5;
			std::stringstream ss;
			ss << "Map " << mapNum + 1;
			map->getComponent<UILabel>().SetLabelText(ss.str());
			map->getComponent<UILabel>().upd();
			return;
		}
		if (expSlider->getComponent<Slider>().hold) {
			Game::exp = expSlider->getComponent<Slider>().value;
			std::stringstream ss;
			ss << "EXP: " << Game::exp;
			exp->getComponent<UILabel>().SetLabelText(ss.str());
			exp->getComponent<UILabel>().upd();
		}
		if (moneySlider->getComponent<Slider>().hold) {
			Game::money = moneySlider->getComponent<Slider>().value;
			std::stringstream ss;
			ss << "Money: " << Game::money;
			money->getComponent<UILabel>().SetLabelText(ss.str());
			money->getComponent<UILabel>().upd();
		}
		if (msSlider->getComponent<Slider>().hold) {
			Game::moneySpeed = msSlider->getComponent<Slider>().value;
			std::stringstream ss;
			ss << "$/s: " << Game::moneySpeed;
			ms->getComponent<UILabel>().SetLabelText(ss.str());
			ms->getComponent<UILabel>().upd();
		}
		if (start->getComponent<MouseButtonComponent>().pressed1) {
			Game::type = Game::S_Server;
			map->destroy();
			mapChangeL->destroy();
			mapChangeR->destroy();
			money->destroy();
			moneySlider->destroy();
			exp->destroy();
			expSlider->destroy();
			ms->destroy();
			msSlider->destroy();
			start->destroy();
			bg->destroy();
			entity->destroy();
			return;
		}
	}
	if (joinmenu) {
		if (start->getComponent<MouseButtonComponent>().pressed1) {
			Game::type = Game::S_Client;
			Game::IP = ELineIP->getComponent<EditLine>().text;
			IPAdrress->destroy();
			ELineIP->destroy();
			start->destroy();
			bg->destroy();
			entity->destroy();
			return;
		}
	}
}
*/