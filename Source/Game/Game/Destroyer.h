#pragma once
#include "Frame/Actor.h"
#include "GameTrack.h"

class Destroyer : public max::Actor {
public:
	Destroyer(const max::Transform& transform) :
		max::Actor{ transform }
	{

	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
};