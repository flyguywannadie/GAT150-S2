#pragma once
#include "PhysicsComponent.h"

namespace max
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLERATION(EnginePhysicsComponent)

		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

		void ApplyTorque(float torque) override;

		void SetTorque(float torque) override;
	};
}