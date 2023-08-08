#pragma once
#include "Enemy.h"

class Beetle : public Enemy {
public:
	Beetle(float speed, int health, int fuelreward, const max::Transform& transform) :
		Enemy{ speed, health, fuelreward, transform }
	{};

	void OnCollision(Actor* other) override;

private:
};