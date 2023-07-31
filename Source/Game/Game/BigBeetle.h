#pragma once
#include "Enemy.h"

class BigBeetle : public Enemy {
public:
	BigBeetle(float speed, int health, int fuelreward, const max::Transform& transform, std::shared_ptr<max::Model> model) :
		Enemy{ speed, health,fuelreward, transform, model }
	{};

	void OnCollision(Actor* other) override;

private:
};