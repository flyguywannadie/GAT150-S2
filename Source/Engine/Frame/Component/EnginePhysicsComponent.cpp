#include "EnginePhysicsComponent.h"
#include "Frame/Actor.h"

namespace max
{
	void max::EnginePhysicsComponent::Update(float dt)
	{
		m_owner->m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void max::EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}
}
