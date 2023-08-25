#pragma once
#include "Frame/Actor.h"

namespace max
{

	class Walls : public max::Actor {
	public:
		CLASS_DECLERATION(Walls);

		/*	Walls(const max::Transform& transform) :
			max::Actor{ transform }
		{};*/

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

		//void Read(const json_t& value);

	protected:
	};
}