#pragma once
#include "Frame/Actor.h"

class Missile : public max::Actor {
public:
	Missile(const max::Transform& transform, std::shared_ptr<max::Model> model) :
		max::Actor{ transform, model }
	{
	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void OnCreate() override;

private:
	bool hit = false;
	float m_hitTimer = 2.5f;
};