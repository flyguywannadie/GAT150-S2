#pragma once
#include "Frame/Actor.h"

class Walls : public max::Actor {
public:
	Walls(const max::Transform& transform) :
		max::Actor{ transform}
	{};

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other);

	//void Read(const json_t& value);

protected:
};