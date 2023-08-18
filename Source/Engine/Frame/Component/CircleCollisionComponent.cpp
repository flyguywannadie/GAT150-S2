#include "CircleCollisionComponent.h"
#include "Frame/Actor.h"

namespace max
{
	CLASS_DEFINITION(CircleCollisionComponent);

	void max::CircleCollisionComponent::Update(float dt)
	{

	}

	bool max::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}

	void max::CircleCollisionComponent::Read(const json_t& value) {
		//
	}
}