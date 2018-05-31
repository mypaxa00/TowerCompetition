#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;
	int width = 0;
	int height = 0;

	float speed = 0;
	float scale = 1;

	TransformComponent() {
		position.Zero();
		width = height = 64;
		scale = 1;
	}

	TransformComponent(float x, float y, float scale = 1, int wNh = 64, int h = 0) {
		width = wNh * scale;
		if(h != 0)
			height = h * scale;
		else 
			height = wNh * scale;
		this->scale = scale;
		position.x = static_cast<float>(x);
		position.y = static_cast<float>(y);
	}
	
	void init() override {
		velocity.Zero();
	}

	void update() override {
		if (speed != 0) {
			float moveSp = speed;
			if (velocity.x != 0 || velocity.y != 0) {
				moveSp = speed / sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
			}
			position.x += velocity.x * moveSp;
			position.y += velocity.y * moveSp;
		}
	}
};