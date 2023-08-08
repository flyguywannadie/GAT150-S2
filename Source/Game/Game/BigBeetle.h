#pragma once
#include "Enemy.h"

class BigBeetle : public Enemy {
public:
	BigBeetle(float speed, int health, int fuelreward, const max::Transform& transform) :
		Enemy{ speed, health,fuelreward, transform }
	{};

	void OnCollision(Actor* other) override;

private:
};