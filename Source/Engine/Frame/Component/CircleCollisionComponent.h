#pragma once
#include "CollisionComponent.h"

namespace max
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLERATION(CircleCollisionComponent)

		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;

	public:

	};
}