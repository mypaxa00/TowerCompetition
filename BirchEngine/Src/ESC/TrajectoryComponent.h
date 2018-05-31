#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class TrajectoryComponent : public Component
{
public:
	TrajectoryComponent(){}
	~TrajectoryComponent(){}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->position.x = prevPos.x = Game::trajectorys[0][0];
		transform->position.y = prevPos.y = Game::trajectorys[0][1];
		angle = &entity->getComponent<SpriteComponent>().angle;
	}

	void update() override {
		if (reached < Game::checkPointCount) {
			Vector2D dist = Vector2D(fabs(Game::trajectorys[reached][0] - transform->position.x)
									, fabs(Game::trajectorys[reached][1] - transform->position.y));
			if (dist < Vector2D(5, 5)) {
				reached++;
				transform->velocity.x = Game::trajectorys[reached][0] - transform->position.x;
				transform->velocity.y = Game::trajectorys[reached][1] - transform->position.y;
				*angle = asin((transform->velocity.x) / sqrt(pow(transform->velocity.x, 2) + pow(transform->velocity.y, 2))) * 180 / M_PI;
				if (transform->velocity.y > 0) {
					if (transform->velocity.x > 0)
						*angle = 180 - *angle;
					else
						*angle = -180 - *angle;
				}
				*angle -= 90;
			}
		}
		else {
			entity->delGroup(Game::G_Enemies);
			entity->destroy();
			Game::health -= 5;
		}
	}

private:
	TransformComponent * transform;
	Vector2D prevPos;
	float * angle;
	int count = 0;
	int reached = 0;
};