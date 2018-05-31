#pragma once

#include "ESC.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
public:
	
	int damage = 0;

	ProjectileComponent(int rng, float sp, int dmg, Vector2D vel, Vector2D* enm = NULL) : range(rng), speed(sp), damage(dmg), velocity(vel), enemy(enm)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->speed = speed;
		transform->velocity = velocity;
		startPos = transform->position;
	}

	void update() override
	{
		curPos = transform->position;
		distance = sqrt(pow(curPos.x - startPos.x, 2) + pow(curPos.y - startPos.y, 2));

		transform->position = curPos;

		if (distance > range)
		{
			entity->destroy();
		}
		else if (transform->position.x > 1920 || transform->position.y > 1080 ||
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
	Vector2D* enemy = NULL;
	Vector2D velocity;
	Vector2D startPos;
	Vector2D curPos;


};