#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Player.h"

namespace max
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<max::PhysicsComponent>();

		return false;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		max::Vector2 direction = transform.position;
		transform.rotation = direction.Angle() - 90.0f;



		max::vec2 forward = max::vec2{ 0,1 }.Rotate(transform.rotation);
		//transform.position += (forward * speed) * max::g_time.GetDeltaTime();
		//transform.position.x = max::Wrap(transform.position.x, (float)max::g_renderer.GetWidth());
		//transform.position.y = max::Wrap(transform.position.y, (float)max::g_renderer.GetHeight());

		m_physicsComponent->SetVelocity(forward * speed);

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Stomping") {
			m_health = 0;
		}

		if (m_health <= 0 && !destroyed) {
			max::EventManager::Instance().DispatchEvent("AddPoints", 100);
			
			destroyed = true;

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
			max::Transform t{ { transform.position.x, transform.position.y }, 0, 1 };
			auto emitter = std::make_unique<max::Emitter>(t, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
	}
	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}