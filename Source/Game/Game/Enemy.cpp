#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Player.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	max::Vector2 direction = m_nextPoint - m_transform.position;
	m_transform.rotation = direction.Angle() - 90.0f;

	max::vec2 forward = max::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += (forward * m_speed) * max::g_time.GetDeltaTime();
	m_transform.position.x = max::Wrap(m_transform.position.x, (float)max::g_renderer.GetWidth());
	m_transform.position.y = max::Wrap(m_transform.position.y, (float)max::g_renderer.GetHeight());

	//std::cout << m_transform.position.Distance(m_nextPoint) << std::endl;

	if (m_transform.position.Distance(m_nextPoint) < 1.0f) {

		m_lastPoint++;
		m_nextPoint = m_track->GetPoint(m_lastPoint);
	}
}

void Enemy::OnCollision(Actor* other)
{
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
		data.color = max::Color{ 1, 1, 0, 1 };
		max::Transform transform{ { m_transform.position.x, m_transform.position.y }, 0, 1 };
		auto emitter = std::make_unique<max::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}