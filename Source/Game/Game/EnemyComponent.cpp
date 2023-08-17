#include "EnemyComponent.h"
#include "Renderer/Renderer.h"
#include "Player.h"

namespace max
{
	bool EnemyComponent::Initialize()
	{
		return false;
	}

	void EnemyComponent::Update(float dt)
	{
		//Component::Update(dt);

		max::Vector2 direction = m_owner->transform.position;
		m_owner->transform.rotation = direction.Angle() - 90.0f;

		max::vec2 forward = max::vec2{ 0,1 }.Rotate(m_owner->transform.rotation);
		m_owner->transform.position += (forward * speed) * max::g_time.GetDeltaTime();
		m_owner->transform.position.x = max::Wrap(m_owner->transform.position.x, (float)max::g_renderer.GetWidth());
		m_owner->transform.position.y = max::Wrap(m_owner->transform.position.y, (float)max::g_renderer.GetHeight());

	}

	void EnemyComponent::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}

	void EnemyComponent::OnCollision(Actor* other)
	{
		if (other->tag == "Stomping") {
			m_health = 0;
		}

		if (m_health <= 0 && !m_owner->destroyed) {
			m_owner->destroyed = true;

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
			max::Transform t{ { m_owner->transform.position.x, m_owner->transform.position.y }, 0, 1 };
			auto emitter = std::make_unique<max::Emitter>(t, data);
			emitter->lifespan = 1.0f;
			m_owner->m_scene->Add(std::move(emitter));
		}
	}
}