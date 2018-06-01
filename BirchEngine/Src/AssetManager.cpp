#include "AssetManager.h"
#include "ESC/Components.h"
#include "Game.h"



AssetManager::AssetManager(Manager* man) : manager(man)
{
}


AssetManager::~AssetManager()
{
}

Entity * AssetManager::CreateButton(int posX, int posY, int width, int height, std::string text, ButtonColor color) {
	SDL_Color white = { 255, 255, 255, 255 };
	auto& button(manager->addEntity());
	button.addComponent<TransformComponent>(posX, posY, 1, width, height);
	switch (color)
	{
	case B_Blue:
		button.addComponent<SpriteComponent>("button_blue", NULL, Vector2D(190, 49));
		button.addComponent<MouseButtonComponent>("button_pressed_blue");
		break;
	case B_Green:
		button.addComponent<SpriteComponent>("button_green", NULL, Vector2D(190, 49));
		button.addComponent<MouseButtonComponent>("button_pressed_green");
		break;
	case B_White:
		button.addComponent<SpriteComponent>("button_white", NULL, Vector2D(190, 49));
		button.addComponent<MouseButtonComponent>("button_pressed_white");
		break;
	case B_Red:
		button.addComponent<SpriteComponent>("button_red", NULL, Vector2D(190, 49));
		button.addComponent<MouseButtonComponent>("button_pressed_red");
		break;
	case B_Yellow:
		button.addComponent<SpriteComponent>("button_yellow", NULL, Vector2D(190, 49));
		button.addComponent<MouseButtonComponent>("button_pressed_yellow");
		break;
	default:
		break;
	}
	button.addComponent<UILabel>(posX + 3, posY + 3, text, "Blocks", white);
	button.addGroup(Game::G_Labels);
	return &button;
}

void AssetManager::CreateTowerPlace(Vector2D pos, std::string id)
{
	auto& towerPlace(manager->addEntity());
	towerPlace.addComponent<TransformComponent>(pos.x, pos.y);
	towerPlace.addComponent<SpriteComponent>(id);
	towerPlace.addComponent<MouseButtonComponent>();
	towerPlace.addComponent<TowerPlaceComponent>(manager, this);
	towerPlace.addGroup(Game::G_Decorations);
}

void AssetManager::CreateTower(Vector2D pos, TowersType type, int range, float speed, int lvl)
{
	auto& postament(manager->addEntity());
	postament.addComponent<TransformComponent>(pos.x, pos.y);
	postament.addComponent<SpriteComponent>("postament");
	postament.addGroup(Game::G_Decorations);
	auto& tower(manager->addEntity());
	tower.addComponent<TransformComponent>(pos.x, pos.y);
	switch (type)
	{
	case AssetManager::Tw_MashineGun:
		tower.addComponent<SpriteComponent>("MachineGun1", NULL, Vector2D(128, 128));
		break;
	case AssetManager::Tw_RocketLauncher:
		tower.addComponent<SpriteComponent>("RocketLauncher1", NULL, Vector2D(128, 128));
		break;
	default:
		break;
	}
	tower.addComponent<EnemyDetect>(manager, this, type, range, speed, lvl);
	tower.addGroup(Game::G_Towers);
}

Entity * AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, float speed, ShotType bull, float* ang, Entity* enemy)
{
	auto& projectile(manager->addEntity());
	switch (bull)
	{
	case AssetManager::Sh_Bullet1:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("bullet1");
		projectile.addComponent<ColliderComponent>("bullet1", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 5, vel);
		break;
	case AssetManager::Sh_Bullet2:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("bullet2");
		projectile.addComponent<ColliderComponent>("bullet2", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 10, vel);
		break;
	case AssetManager::Sh_Bullet3:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("bullet3");
		projectile.addComponent<ColliderComponent>("bullet3", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 15, vel);
		break;
	case AssetManager::Sh_Bullet4:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("bullet4");
		projectile.addComponent<ColliderComponent>("bullet4", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 20, vel);
		break;
	case AssetManager::Sh_Rocket1:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("rocket1", *ang, Vector2D(128, 128));
		projectile.addComponent<ColliderComponent>("rocket1", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 5, vel , enemy);
		break;
	case AssetManager::Sh_Rocket2:
		projectile.addComponent<TransformComponent>(pos.x, pos.y);
		projectile.addComponent<SpriteComponent>("rocket2", *ang, Vector2D(128, 128));
		projectile.addComponent<ColliderComponent>("rocket2", 15, 15);
		projectile.addComponent<ProjectileComponent>(range, speed, 10, vel , enemy);
		break;
	default:
		break;
	}
	
	projectile.addGroup(Game::G_Projectiles);
	return &projectile;
}

void AssetManager::CreateEnemy(EnemyType enemy)
{
	auto& en(manager->addEntity());
	en.addComponent<TransformComponent>();
	switch (enemy)
	{
	case AssetManager::E_Soldier1:
		en.addComponent<SpriteComponent>("soldier1");
		en.getComponent<TransformComponent>().speed = 1.5;
		en.addComponent<HealthComponent>(manager, 100);
		en.addComponent<ColliderComponent>("enemy", 20, 20);
		break;
	case AssetManager::E_Soldier2:
		en.addComponent<SpriteComponent>("soldier2");
		en.getComponent<TransformComponent>().speed =  2;
		en.addComponent<HealthComponent>(manager, 110);
		en.addComponent<ColliderComponent>("enemy", 20, 20);
		break;
	case AssetManager::E_Soldier3:
		en.addComponent<SpriteComponent>("soldier3");
		en.getComponent<TransformComponent>().speed = 2.5;
		en.addComponent<HealthComponent>(manager, 125);
		en.addComponent<ColliderComponent>("enemy", 20, 20);
		break;
	case AssetManager::E_Soldier4:
		en.addComponent<SpriteComponent>("soldier4");
		en.getComponent<TransformComponent>().speed = 3;
		en.addComponent<HealthComponent>(manager, 150);
		en.addComponent<ColliderComponent>("enemy", 20, 20);
		break;
	case AssetManager::E_Plane1:
		en.addComponent<SpriteComponent>("plane1");
		en.getComponent<TransformComponent>().speed = 3;
		en.getComponent<TransformComponent>().scale = 1.1;
		en.addComponent<HealthComponent>(manager, 90);
		en.addComponent<Shadow>(manager, "planeShd1");
		en.addComponent<ColliderComponent>("enemy", 35, 35);
		break;
	case AssetManager::E_Plane2:
		en.addComponent<SpriteComponent>("plane2");
		en.getComponent<TransformComponent>().speed = 5;
		en.getComponent<TransformComponent>().scale = 1.1;
		en.addComponent<HealthComponent>(manager, 100);
		en.addComponent<Shadow>(manager, "planeShd2");
		en.addComponent<ColliderComponent>("enemy", 35, 35);
		break;
	default:
		break;
	}
	en.addComponent<TrajectoryComponent>();
	en.addGroup(Game::G_Enemies);
}

void AssetManager::AddTexture(std::string id, const char * path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture * AssetManager::GetTexture(std::string id)
{
	if (textures[id] == NULL) {
		std::cout << "No such texture: \"" << id << "\"" << std::endl;
	}
	return textures[id];
}

void AssetManager::AddFont(std::string id, const char * path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font * AssetManager::GetFont(std::string id)
{
	if (fonts[id] == NULL)
		std::cout << "No such font: \"" << id << "\"" << std::endl;
	return fonts[id];
}
