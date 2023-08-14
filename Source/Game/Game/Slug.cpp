#include "Slug.h"

void Slug::OnCollision(Actor* other) {
	if (other->m_tag == "Stomping") {
		m_health = 0;
		dynamic_cast<Squisher*>(m_game)->m_fuel += m_fuelReward;
	}
	else if (other->m_tag == "Lazer" || other->m_tag == "Red_Hot") {
		m_health--;
	}
	else if (other->m_tag == "Destroyer") {
		m_health = 0;
	}
	else if (other->m_tag == "BigBoom") {
		m_health-= 50;
	}

	if (m_health <= 0 && !m_destroyed) {
		m_destroyed = true;

		m_spawner->m_enemiesKilled++;

		max::g_audioSystem.PlayOneShot("hit", false);

		max::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = max::Pi;
		data.lifetimeMin = 0.25f;
		data.lifetimeMin = 1.0f;
		data.speedMin = 50;
		data.speedMax = 150;
		data.damping = 0.5f;
		data.color = max::Color{ 0.5, 0.6, 0.3, 1 }; //m_model->GetColor();;
		max::Transform transform{ { m_transform.position.x, m_transform.position.y }, 0, 1 };
		auto emitter = std::make_unique<max::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}