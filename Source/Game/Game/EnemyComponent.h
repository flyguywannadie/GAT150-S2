#pragma once
#include "Frame/Component/Component.h"
#include "Frame/Emitter.h"
#include "Audio/AudioSystem.h"
#include "Squisher.h"
#include "Frame/Scene.h"

namespace max
{
	class EnemyComponent : public max::Component {
	public:
		//Enemy(float speed, int health, const max::Transform& transform) :
		//	max::Actor{ transform},
		//	m_speed{ speed },
		//	m_health{ health }
		//{};

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* other);

		void Read(const json_t& value);

	protected:
		float speed = 0;
		int m_health = 0;
		int m_damage = 0;
	};
}
