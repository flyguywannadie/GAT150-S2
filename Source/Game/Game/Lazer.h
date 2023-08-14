#pragma once
#include "Frame/Actor.h"

class Lazer : public max::Actor {
public:
	Lazer(const max::Transform& transform) :
		max::Actor{ transform }
	{
	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	bool Initialize() override;

private:
	float speed = 5;
	float baseScale = 1;
};