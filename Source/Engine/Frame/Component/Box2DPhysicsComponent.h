#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

class b2Body;

namespace max
{
	class Box2DPhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLERATION(Box2DPhysicsComponent)

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;
		virtual void SetVelocity(const vec2& velocity) override;

		friend class BoxCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}