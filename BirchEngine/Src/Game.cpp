#include "Game.h"
#include "ESC/ESC.h"
#include "TextureManager.h"
#include "ESC/Components.h"
#include "Map.h"
#include "Collision.h"
#include <sstream>

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager * Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

int Game::health = 100;
float Game::money = 1000;
int Game::exp = 0;
int Game::moneySpeed = 1;
std::string Game::map = "Assets/maps/map.map";
std::string Game::decorations = "Assets/maps/decorations.map";
std::string Game::trajectory = "Assets/maps/trajectory.map";
int Game::checkPointCount = 7;
int Game::trajectorys[16][2];

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& moneyLabel(manager.addEntity());
auto& expLabel(manager.addEntity());
auto& healthLabel(manager.addEntity());
auto& hud(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_RESIZABLE;
	
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, 100, 100, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//Loading Textures
		//Map
		if(true){
		assets->AddTexture("0", "Assets/tiles/64/environment/m_dirt_tile.png");
		assets->AddTexture("1", "Assets/tiles/64/environment/m_grass_tile.png");
		assets->AddTexture("2", "Assets/tiles/64/environment/m_road_tile.png");
		assets->AddTexture("3", "Assets/tiles/64/environment/m_sand_tile.png");
		assets->AddTexture("4", "Assets/tiles/64/environment/m_dirt_cleen_tile.png");
		assets->AddTexture("5", "Assets/tiles/64/environment/m_grass_cleen_tile.png");
		assets->AddTexture("6", "Assets/tiles/64/environment/m_road_cleen_tile.png");
		assets->AddTexture("7", "Assets/tiles/64/environment/m_sand_cleen_tile.png");
		assets->AddTexture("8", "Assets/tiles/64/environment/1.png");
		assets->AddTexture("9", "Assets/tiles/64/environment/2.png");
		assets->AddTexture("10", "Assets/tiles/64/environment/3.png");
		assets->AddTexture("11", "Assets/tiles/64/environment/4.png");
		assets->AddTexture("12", "Assets/tiles/64/environment/5.png");
		assets->AddTexture("13", "Assets/tiles/64/environment/6.png");
		assets->AddTexture("14", "Assets/tiles/64/environment/7.png");
		assets->AddTexture("15", "Assets/tiles/64/environment/8.png");
		assets->AddTexture("16", "Assets/tiles/64/environment/9.png");
		assets->AddTexture("17", "Assets/tiles/64/environment/10.png");
		assets->AddTexture("18", "Assets/tiles/64/environment/11.png");
		assets->AddTexture("19", "Assets/tiles/64/environment/12.png");
		assets->AddTexture("20", "Assets/tiles/64/environment/13.png");
		assets->AddTexture("21", "Assets/tiles/64/environment/14.png");
		assets->AddTexture("22", "Assets/tiles/64/environment/15.png");
		assets->AddTexture("23", "Assets/tiles/64/environment/16.png");
		assets->AddTexture("24", "Assets/tiles/64/environment/17.png");
		assets->AddTexture("25", "Assets/tiles/64/environment/18.png");
		assets->AddTexture("26", "Assets/tiles/64/environment/19.png");
		assets->AddTexture("27", "Assets/tiles/64/environment/20.png");
		assets->AddTexture("28", "Assets/tiles/64/environment/21.png");
		assets->AddTexture("29", "Assets/tiles/64/environment/22.png");
		assets->AddTexture("30", "Assets/tiles/64/environment/23.png");
		assets->AddTexture("31", "Assets/tiles/64/environment/24.png");
		assets->AddTexture("32", "Assets/tiles/64/environment/25.png");
		assets->AddTexture("33", "Assets/tiles/64/environment/26.png");
		assets->AddTexture("34", "Assets/tiles/64/environment/27.png");
		assets->AddTexture("35", "Assets/tiles/64/environment/28.png");
		assets->AddTexture("36", "Assets/tiles/64/environment/29.png");
		assets->AddTexture("37", "Assets/tiles/64/environment/30.png");
		assets->AddTexture("38", "Assets/tiles/64/environment/31.png");
		assets->AddTexture("39", "Assets/tiles/64/environment/32.png");
		assets->AddTexture("40", "Assets/tiles/64/environment/33.png");
		assets->AddTexture("41", "Assets/tiles/64/environment/34.png");
		assets->AddTexture("42", "Assets/tiles/64/environment/35.png");
		assets->AddTexture("43", "Assets/tiles/64/environment/36.png");
		assets->AddTexture("44", "Assets/tiles/64/environment/37.png");
		assets->AddTexture("45", "Assets/tiles/64/environment/38.png");
		assets->AddTexture("46", "Assets/tiles/64/environment/39.png");
		assets->AddTexture("47", "Assets/tiles/64/environment/40.png");
		assets->AddTexture("48", "Assets/tiles/64/environment/41.png");
		assets->AddTexture("49", "Assets/tiles/64/environment/42.png");
		assets->AddTexture("50", "Assets/tiles/64/environment/43.png");
		assets->AddTexture("51", "Assets/tiles/64/environment/44.png");
		assets->AddTexture("52", "Assets/tiles/64/environment/45.png");
		assets->AddTexture("53", "Assets/tiles/64/environment/46.png");
		assets->AddTexture("54", "Assets/tiles/64/environment/47.png");
		assets->AddTexture("55", "Assets/tiles/64/environment/48.png");
		assets->AddTexture("56", "Assets/tiles/64/environment/49.png");
		assets->AddTexture("57", "Assets/tiles/64/environment/50.png");
		assets->AddTexture("58", "Assets/tiles/64/environment/51.png");
		assets->AddTexture("59", "Assets/tiles/64/environment/52.png");
		assets->AddTexture("60", "Assets/tiles/64/environment/53.png");
		assets->AddTexture("61", "Assets/tiles/64/environment/54.png");
		assets->AddTexture("62", "Assets/tiles/64/environment/55.png");
		assets->AddTexture("63", "Assets/tiles/64/environment/56.png");
		assets->AddTexture("64", "Assets/tiles/64/environment/57.png");
		assets->AddTexture("65", "Assets/tiles/64/environment/58.png");
		assets->AddTexture("66", "Assets/tiles/64/environment/59.png");
		assets->AddTexture("67", "Assets/tiles/64/environment/60.png");
		assets->AddTexture("68", "Assets/tiles/64/environment/61.png");
		assets->AddTexture("69", "Assets/tiles/64/environment/62.png");
		assets->AddTexture("70", "Assets/tiles/64/environment/63.png");
		assets->AddTexture("71", "Assets/tiles/64/environment/64.png");
		assets->AddTexture("72", "Assets/tiles/64/environment/65.png");
		assets->AddTexture("73", "Assets/tiles/64/environment/66.png");
		assets->AddTexture("74", "Assets/tiles/64/environment/67.png");
		assets->AddTexture("75", "Assets/tiles/64/environment/68.png");
		assets->AddTexture("76", "Assets/tiles/64/environment/69.png");
		assets->AddTexture("77", "Assets/tiles/64/environment/70.png");
		assets->AddTexture("78", "Assets/tiles/64/environment/71.png");
		assets->AddTexture("79", "Assets/tiles/64/environment/72.png");
		assets->AddTexture("80", "Assets/tiles/64/environment/73.png");
		assets->AddTexture("81", "Assets/tiles/64/environment/74.png");
		assets->AddTexture("82", "Assets/tiles/64/environment/75.png");
		assets->AddTexture("83", "Assets/tiles/64/environment/76.png");
		assets->AddTexture("84", "Assets/tiles/64/environment/77.png");
		assets->AddTexture("85", "Assets/tiles/64/environment/78.png");
		assets->AddTexture("86", "Assets/tiles/64/environment/79.png");
		assets->AddTexture("87", "Assets/tiles/64/environment/80.png");
		assets->AddTexture("88", "Assets/tiles/64/environment/81.png");
		assets->AddTexture("89", "Assets/tiles/64/environment/82.png");
		assets->AddTexture("90", "Assets/tiles/64/environment/83.png");
		assets->AddTexture("91", "Assets/tiles/64/environment/84.png");
		assets->AddTexture("92", "Assets/tiles/64/environment/85.png");
		assets->AddTexture("93", "Assets/tiles/64/environment/86.png");
		assets->AddTexture("94", "Assets/tiles/64/environment/87.png");
		assets->AddTexture("95", "Assets/tiles/64/environment/88.png");
		assets->AddTexture("96", "Assets/tiles/64/environment/89.png");
		assets->AddTexture("97", "Assets/tiles/64/environment/90.png");
		assets->AddTexture("98", "Assets/tiles/64/environment/91.png");
		assets->AddTexture("99", "Assets/tiles/64/environment/92.png");
		assets->AddTexture("100", "Assets/tiles/64/environment/93.png");
		assets->AddTexture("101", "Assets/tiles/64/environment/94.png");
		assets->AddTexture("102", "Assets/tiles/64/environment/95.png");
		assets->AddTexture("103", "Assets/tiles/64/environment/96.png");
		assets->AddTexture("104", "Assets/tiles/64/environment/97.png");
		assets->AddTexture("105", "Assets/tiles/64/environment/98.png");
		assets->AddTexture("106", "Assets/tiles/64/environment/99.png");
		assets->AddTexture("107", "Assets/tiles/64/environment/100.png");
		assets->AddTexture("108", "Assets/tiles/64/environment/101.png");
		assets->AddTexture("109", "Assets/tiles/64/environment/102.png");
		assets->AddTexture("110", "Assets/tiles/64/environment/103.png");
		assets->AddTexture("111", "Assets/tiles/64/environment/104.png");
		assets->AddTexture("112", "Assets/tiles/64/environment/105.png");
		assets->AddTexture("113", "Assets/tiles/64/environment/106.png");
		assets->AddTexture("114", "Assets/tiles/64/environment/107.png");
		assets->AddTexture("115", "Assets/tiles/64/environment/108.png");
		assets->AddTexture("116", "Assets/tiles/64/environment/109.png");
		assets->AddTexture("117", "Assets/tiles/64/environment/110.png");
		assets->AddTexture("118", "Assets/tiles/64/environment/111.png");
		assets->AddTexture("119", "Assets/tiles/64/environment/112.png");
		assets->AddTexture("120", "Assets/tiles/64/environment/113.png");
		assets->AddTexture("121", "Assets/tiles/64/environment/114.png");
		assets->AddTexture("122", "Assets/tiles/64/environment/115.png");
		assets->AddTexture("123", "Assets/tiles/64/environment/116.png");
		assets->AddTexture("124", "Assets/tiles/64/environment/117.png");
		assets->AddTexture("125", "Assets/tiles/64/environment/118.png");
		assets->AddTexture("126", "Assets/tiles/64/environment/119.png");
		assets->AddTexture("127", "Assets/tiles/64/environment/120.png");
		assets->AddTexture("128", "Assets/tiles/64/environment/121.png");
		assets->AddTexture("129", "Assets/tiles/64/environment/122.png");
		assets->AddTexture("130", "Assets/tiles/64/environment/123.png");
		assets->AddTexture("131", "Assets/tiles/64/environment/124.png");
		assets->AddTexture("132", "Assets/tiles/64/environment/125.png");
		assets->AddTexture("133", "Assets/tiles/64/environment/126.png");
		assets->AddTexture("134", "Assets/tiles/64/environment/127.png");
		assets->AddTexture("135", "Assets/tiles/64/environment/128.png");
		assets->AddTexture("136", "Assets/tiles/64/environment/129.png");
		assets->AddTexture("137", "Assets/tiles/64/environment/130.png");
		assets->AddTexture("138", "Assets/tiles/64/environment/131.png");
		assets->AddTexture("139", "Assets/tiles/64/environment/132.png");
		assets->AddTexture("140", "Assets/tiles/64/environment/133.png");
		assets->AddTexture("141", "Assets/tiles/64/environment/134.png");
		assets->AddTexture("142", "Assets/tiles/64/environment/135.png");
		assets->AddTexture("143", "Assets/tiles/64/environment/136.png");
		assets->AddTexture("144", "Assets/tiles/64/environment/137.png");
		assets->AddTexture("145", "Assets/tiles/64/environment/138.png");
		assets->AddTexture("146", "Assets/tiles/64/environment/139.png");
		assets->AddTexture("147", "Assets/tiles/64/environment/140.png");
		assets->AddTexture("148", "Assets/tiles/64/environment/141.png");
		assets->AddTexture("149", "Assets/tiles/64/environment/142.png");
		assets->AddTexture("150", "Assets/tiles/64/environment/143.png");
		assets->AddTexture("151", "Assets/tiles/64/environment/144.png");
		assets->AddTexture("152", "Assets/tiles/64/environment/145.png");
		assets->AddTexture("153", "Assets/tiles/64/environment/146.png");
		assets->AddTexture("154", "Assets/tiles/64/environment/147.png");
		assets->AddTexture("155", "Assets/tiles/64/environment/148.png");
		assets->AddTexture("156", "Assets/tiles/64/environment/149.png");
		assets->AddTexture("157", "Assets/tiles/64/environment/150.png");
		assets->AddTexture("158", "Assets/tiles/64/environment/151.png");
		assets->AddTexture("159", "Assets/tiles/64/environment/152.png");
		assets->AddTexture("160", "Assets/tiles/64/environment/153.png");
		assets->AddTexture("161", "Assets/tiles/64/environment/154.png");
		assets->AddTexture("162", "Assets/tiles/64/environment/155.png");
		assets->AddTexture("163", "Assets/tiles/64/environment/156.png");
		assets->AddTexture("164", "Assets/tiles/64/environment/decorations/dec_rock1_tile.png");
		assets->AddTexture("165", "Assets/tiles/64/environment/decorations/dec_rock2_tile.png");
		assets->AddTexture("166", "Assets/tiles/64/environment/decorations/dec_rock3_tile.png");
		assets->AddTexture("167", "Assets/tiles/64/environment/decorations/dec_shrub1_tile.png");
		assets->AddTexture("168", "Assets/tiles/64/environment/decorations/dec_shrub2_tile.png");
		assets->AddTexture("169", "Assets/tiles/64/environment/decorations/dec_shrub3_tile.png");
		assets->AddTexture("170", "Assets/tiles/64/environment/decorations/dec_shrub4_tile.png");
		assets->AddTexture("171", "Assets/tiles/64/environment/decorations/dec_shrub5_tile.png");
		assets->AddTexture("172", "Assets/tiles/64/environment/decorations/particles_crater1_tile.png");
		assets->AddTexture("173", "Assets/tiles/64/environment/decorations/particles_crater2_tile.png");
		assets->AddTexture("174", "Assets/tiles/64/environment/decorations/particles_crater3_tile.png");
	}
		
		//Other Textures
		if(true){
			assets->AddTexture("hud_bg", "Assets/ui/grey_button15.png");
			assets->AddTexture("button_blue", "Assets/ui/blue_button00.png");
			assets->AddTexture("button_pressed_blue", "Assets/ui/blue_button01.png");
			assets->AddTexture("selection", "Assets/tiles/64/selection.png");
			assets->AddTexture("tower_place_grass", "Assets/tiles/64/environment/towerDefense_tile045.png");
			assets->AddTexture("tower_place_dirt", "Assets/tiles/64/environment/towerDefense_tile068.png");
			assets->AddTexture("tower_place_sand", "Assets/tiles/64/environment/towerDefense_tile114.png");
			assets->AddTexture("tower_place_road", "Assets/tiles/64/environment/towerDefense_tile091.png");
			assets->AddTexture("MachineGun1", "Assets/tiles/128/towers/towerDefense_tile249.png");
			assets->AddTexture("RocketLauncher1", "Assets/tiles/128/towers/towerDefense_tile204.png");
			assets->AddTexture("postament", "Assets/tiles/64/towers/towerDefense_tile181.png");
			assets->AddTexture("rocket1", "Assets/tiles/128/towers/towerDefense_tile251.png");
			assets->AddTexture("rocket2", "Assets/tiles/128/towers/towerDefense_tile252.png");
			assets->AddTexture("bullet1", "Assets/tiles/64/towers/bullet1_tile.png");
			assets->AddTexture("bullet2", "Assets/tiles/64/towers/bullet2_tile.png");
			assets->AddTexture("bullet3", "Assets/tiles/64/towers/bullet3_tile.png");
			assets->AddTexture("bullet4", "Assets/tiles/64/towers/bullet4_tile.png");
			assets->AddTexture("soldier4", "Assets/tiles/64/enemies/e_soldier4_tile.png");
			assets->AddTexture("soldier3", "Assets/tiles/64/enemies/e_soldier3_tile.png");
			assets->AddTexture("soldier2", "Assets/tiles/64/enemies/e_soldier2_tile.png");
			assets->AddTexture("soldier1", "Assets/tiles/64/enemies/e_soldier1_tile.png");
			assets->AddTexture("plane1", "Assets/tiles/64/enemies/e_plane1_tile.png");
			assets->AddTexture("plane2", "Assets/tiles/64/enemies/e_plane2_tile.png");
	}
	
	
	//Loading Fonts
		{
		assets->AddFont("Future18", "Assets/Fonts/Kenney Future.ttf", 18);
		assets->AddFont("Future", "Assets/Fonts/Kenney Future.ttf", 36);
		assets->AddFont("Blocks", "Assets/Fonts/DS Stamper.ttf", 10);
		assets->AddFont("Square25", "Assets/Fonts/Kenney High Square.ttf", 25);
		assets->AddFont("Rocket", "Assets/Fonts/Kenney Rocket Square.ttf", 45);
		assets->AddFont("Mini", "Assets/Fonts/Kenney Mini.ttf", 45);
	}
	


	/* settings 
	 * @TODO 
	 */
	
	//=====Testing AREA=====
		/* Test Comment */

	//======================

	//ecs


	Map::LoadMap();
	hud.addComponent<TransformComponent>(-64, 1024, 1, 2048, 56);
	hud.addComponent<SpriteComponent>("hud_bg", NULL, Vector2D(190, 49));

	player.addComponent<TransformComponent>(0, 0);
	player.addComponent<SpriteComponent>("soldier4");
	player.addComponent<KeyBoardController>(3);
	player.addComponent<ColliderComponent>("player", 32, 32);
	player.addComponent<HealthComponent>(&manager, 100);
	player.addComponent<LineComponent>(&manager);
	player.addGroup(G_Enemies);

	SDL_Color color = { 255, 255, 255, 255 };
	label.addComponent<UILabel>(10, 10, "", "Future", color);
	label.addGroup(G_Labels);
	color = { 0, 0, 0, 255 };
	moneyLabel.addComponent<UILabel>(10, 1025, "", "Future", color);
	moneyLabel.addGroup(G_Labels);
	color = { 0, 0, 255, 255 };
	expLabel.addComponent<UILabel>(450, 1025, "", "Future", color);
	expLabel.addGroup(G_Labels);
	color = { 255, 0, 0, 255 };
	healthLabel.addComponent<UILabel>(1600, 1025, "", "Future", color);
	healthLabel.addGroup(G_Labels);


	assets->CreateTowerPlace(Vector2D(64 * 8, 64 * 9), "tower_place_grass");
	assets->CreateTowerPlace(Vector2D(64 * 10, 64 * 9), "tower_place_grass");
	assets->CreateTowerPlace(Vector2D(64 * 15, 64 * 9), "tower_place_grass");
}

auto& tiles = manager.getGroup(Game::G_Map);
auto& decor(manager.getGroup(Game::G_Decorations));
auto& enemies(manager.getGroup(Game::G_Enemies));
auto& towers(manager.getGroup(Game::G_Towers));
auto& projectiles(manager.getGroup(Game::G_Projectiles));
auto& colliders(manager.getGroup(Game::G_Colliders));
auto& labels(manager.getGroup(Game::G_Labels));

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}

	switch (event.type)
	{
	case SDL_KEYUP:
		if (Game::event.key.keysym.sym == SDLK_ESCAPE)
			isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_1:
			assets->CreateEnemy(AssetManager::E_Soldier1);
			break;
		case SDLK_2:
			assets->CreateEnemy(AssetManager::E_Soldier2);
			break;
		case SDLK_3:
			assets->CreateEnemy(AssetManager::E_Soldier3);
			break;
		case SDLK_4:
			assets->CreateEnemy(AssetManager::E_Soldier4);
			break;
		case SDLK_5:
			assets->CreateEnemy(AssetManager::E_Plane1);
			break;
		case SDLK_6:
			assets->CreateEnemy(AssetManager::E_Plane2);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Game::update()
{	
	int delay = static_cast<int>((SDL_GetTicks() / 31) % 2);
	if (prevTime != delay) {
		money += (float)moneySpeed / 32;
		prevTime = delay;
	}
	/*int spawnDelay = static_cast<int>((SDL_GetTicks() / 5000) % 2);
	if (prevSpawnTime != spawnDelay) {
		assets->CreateEnemy();
		prevSpawnTime = spawnDelay;
	}*/


	std::stringstream sh;
	sh << "HEALTH: " << health;
	healthLabel.getComponent<UILabel>().SetLabelText(sh.str(), "Future");
	std::stringstream sm;
	sm << "MONEY: " << (int)money;
	moneyLabel.getComponent<UILabel>().SetLabelText(sm.str(), "Future");
	std::stringstream se;
	se << "EXP: " << exp;
	expLabel.getComponent<UILabel>().SetLabelText(se.str(), "Future");
	manager.refresh();
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player.draw();
	for (auto& t : tiles)
		t->draw();
	for (auto& d : decor)
		d->draw();
	for (auto& e : enemies)
		e->draw();
	for (auto& t : towers)
		t->draw();
	for (auto& p : projectiles)
		p->draw();
	hud.draw();
	for (auto& l : labels)
		l->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(id, x, y);
	tile.addGroup(G_Map);
}

void Game::AddDecoration(int id, int x, int y)
{
	if (id != 1000) {
		auto& tile(manager.addEntity());
		tile.addComponent<TileComponent>(id, x, y);
		tile.addGroup(G_Decorations);
	}
}
