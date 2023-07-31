#pragma once
#include "Frame/Actor.h"
#include "GameTrack.h"

class Destroyer : public max::Actor {
public:
	Destroyer(const max::Transform& transform, std::shared_ptr<max::Model> model) :
		max::Actor{ transform, model }
	{};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
};