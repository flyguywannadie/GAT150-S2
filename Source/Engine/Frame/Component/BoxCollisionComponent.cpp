#include "BoxCollisionComponent.h"
#include "Box2DPhysicsComponent.h"
#include "Frame/Actor.h"
#include "SpriteComponent.h"

namespace max
{
	CLASS_DEFINITION(BoxCollisionComponent)

	bool BoxCollisionComponent::Initialize()
	{
		auto component = m_owner->GetComponent<Box2DPhysicsComponent>();
		if (component)
		{
			if (data.size.x == 0 && data.size.y == 0) 
			{
				auto spriteComponent = m_owner->GetComponent<SpriteComponent>();
				if (spriteComponent) 
				{
					data.size = vec2{ spriteComponent->source.w, spriteComponent->source.h };
				}
			}

			data.size = data.size * scaleOffset * m_owner->transform.scale;

			if (component->m_body->GetType() == b2_staticBody)
			{
				PhysicsSystem::Instance().SetCollisionBoxStatic(component->m_body, data, m_owner);
			}
			else
			{
				PhysicsSystem::Instance().SetCollisionBox(component->m_body, data, m_owner);
			}
		}

		return true;
	}

	void BoxCollisionComponent::Update(float dt)
	{
	}

	void BoxCollisionComponent::Read(const json_t& value)
	{
		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "restitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);
	}
}