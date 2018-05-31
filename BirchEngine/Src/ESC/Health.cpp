#include "Health.h"

void HealthComponent::update()
{
	for (auto& s : *shot) {
		if (Collision::AABB(entity->getComponent<ColliderComponent>().collider, s->getComponent<ColliderComponent>().collider))
		{
			health -= s->getComponent<ProjectileComponent>().damage;
			s->destroy();
		}
	}
	if (label->isActive() == 1) {
		std::stringstream hlth;
		hlth << health;
		if (health > maxHealth / 3 * 2) {
			label->getComponent<UILabel>().SetLabelText(hlth.str(), "Future18", green, position->x + 18, position->y - 5);
		}
		else if (health < maxHealth / 3) {
			label->getComponent<UILabel>().SetLabelText(hlth.str(), "Future18", red, position->x + 18, position->y - 5);
		}
		else
			label->getComponent<UILabel>().SetLabelText(hlth.str(), "Future18", yellow, position->x + 18, position->y - 5);
	}
	if (health <= 0) {
		entity->destroy();
		label->destroy();
		Game::exp += 15;
	}
}