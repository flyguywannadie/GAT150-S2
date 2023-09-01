#pragma once
#include "Frame/Actor.h"
#include "Frame/Component/PhysicsComponent.h"
#include "Frame/Component/ModelRenderComponent.h"

namespace max
{
	class Player : public max::Actor {
	public:
		CLASS_DECLERATION(Player)

		//Player(float speed, float turnRate, const max::Transform& transform) :
		//	max::Actor{ transform },
		//	speed{ speed },
		//	m_turnRate{ turnRate }
		//{
		//	m_health = 10;
		//};

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;
		void Draw(max::Renderer& renderer) override;

		bool squishin = false;
		bool beinsqished = false;

	private:
		float speed = 0;
		float m_turnRate = 0;


		max::PhysicsComponent* m_physicsComponent = nullptr;
		max::ModelRenderComponent* m_modelRenderComponent = nullptr;
	};
}