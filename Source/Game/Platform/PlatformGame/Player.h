#pragma once
#include "Frame/Actor.h"
#include "Frame/Component/PhysicsComponent.h"
#include "Frame/Component/ModelRenderComponent.h"

namespace max
{
	class Player : public max::Actor {
	public:
		CLASS_DECLERATION(Player)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;


		max::PhysicsComponent* m_physicsComponent = nullptr;
	};
}