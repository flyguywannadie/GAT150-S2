#include "CircleCollisionComponent.h"
#include "Frame/Actor.h"

namespace max
{
	void max::CircleCollisionComponent::Update(float dt)
	{

	}

	bool max::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->m_transform.position.Distance(collision->m_owner->m_transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}
}