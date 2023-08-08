#pragma once
#include "Enemy.h"

class Slug : public Enemy {
public:
	Slug(float speed, int health, int fuelreward,const max::Transform& transform) :
		Enemy{speed, health, fuelreward, transform }
	{};

	void OnCollision(Actor* other) override;
private:
};