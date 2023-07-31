#pragma once
#include "Frame/Actor.h"

class Lazer : public max::Actor {
public:
	Lazer(const max::Transform& transform, std::shared_ptr<max::Model> model) :
		max::Actor{ transform, model }
	{
	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void OnCreate() override;

private:
	float speed = 5;
};