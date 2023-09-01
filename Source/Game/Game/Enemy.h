#pragma once
#include "Frame/Actor.h"
#include "Frame/Emitter.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Squisher.h"
#include "Frame/Scene.h"
#include "Frame/Component/PhysicsComponent.h"

namespace max
{
	class Enemy : public max::Actor {
	public:
		CLASS_DECLERATION(Enemy)

		//Enemy(float speed, int health, const max::Transform& transform) :
		//	max::Actor{ transform},
		//	m_speed{ speed },
		//	m_health{ health }
		//{};

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other);
		void OnCollisionExit(Actor* other);

		//void Read(const json_t& value);

	protected:
		float speed = 0;
		int m_health = 0;
		int m_damage = 0;

		bool grabbed = false;
		Player* m_player = nullptr;

		max::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
