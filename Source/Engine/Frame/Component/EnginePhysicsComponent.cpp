#include "EnginePhysicsComponent.h"
#include "Frame/Actor.h"

namespace max
{
	CLASS_DEFINITION(EnginePhysicsComponent);

	void max::EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void max::EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void EnginePhysicsComponent::ApplyTorque(float torque)
	{
		//
	}

	void max::EnginePhysicsComponent::Read(const json_t& value) {
		//
	}
}
