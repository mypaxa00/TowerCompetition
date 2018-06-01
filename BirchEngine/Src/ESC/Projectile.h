#pragma once

#include "ESC.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	
	int damage = 0;

	ProjectileComponent(int rng, float sp, int dmg, Vector2D vel, Entity* enm = NULL) : range(rng), speed(sp), damage(dmg), velocity(vel), enemy(enm)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->speed = speed;
		transform->velocity = velocity;
		startPos = transform->position;
		curPos = &transform->position;
	}

	void update() override
	{

		if (enemy != NULL && enemy->isActive() == 1 && enemy->hasGroup(Game::G_Enemies)) {
			Vector2D dir = transform->velocity = Vector2D(enemy->getComponent<TransformComponent>().position.x - curPos->x, enemy->getComponent<TransformComponent>().position.y - curPos->y);
			float * angle = &entity->getComponent<SpriteComponent>().angle;
			distance = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
			*angle = asin((dir.x) / distance) * 180 / M_PI;
			if (dir.y > 0) {
				if (dir.x > 0)
					*angle = 180 - *angle;
				else
					*angle = -180 - *angle;
			}
		}
		else
		{
			distance = sqrt(pow(curPos->x - startPos.x, 2) + pow(curPos->y - startPos.y, 2));

			if (distance > range)
			{
				entity->destroy();
			}
		}
		if (transform->position.x > 1920 || transform->position.y > 1080 ||
			transform->position.x < -64 || transform->position.y < -64)
		{
			entity->destroy();
		}

	}

private:

	TransformComponent* transform;
	int range = 0;
	float speed = 0;
	float distance = 0;
	Entity* enemy = NULL;
	Vector2D velocity;
	Vector2D startPos;
	Vector2D * curPos;


};