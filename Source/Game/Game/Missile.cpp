#include "Missile.h"
#include "Input/InputSystem.h"
#include "Frame/Scene.h"
#include "Frame/Emitter.h"
#include "Squisher.h"
#include "Renderer/ModelManager.h"

void Missile::OnCreate()
{
	dynamic_cast<Squisher*>(m_game)->m_fuel -= 20;
	dynamic_cast<Squisher*>(m_game)->SetWeaponTimer(1.5f);
}

void Missile::Update(float dt)
{
	Actor::Update(dt);

	if (!hit) {
		m_hitTimer -= dt;
		if (m_hitTimer <= 0)
		{
			max::EmitterData data;
			data.burst = true;
			data.burstCount = 1000;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = max::Pi;
			data.lifetimeMin = 0.25f;
			data.lifetimeMin = 0.5f;
			data.speedMin = 50;
			data.speedMax = 150;
			data.damping = 0.2f;
			data.color = max::Color{ 0.7f, 0.7f, 0.7f, 1 };
			max::Transform transform{ { m_transform.position }, 0, 1 };
			auto emitter = std::make_unique<max::Emitter>(transform, data);
			emitter->m_lifespan = 0.4f;
			emitter->m_tag = "BigBoom";
			m_scene->Add(std::move(emitter));

			m_model = max::g_ModelManager.Get("bigboom.txt");
			m_tag = "BigBoom";
			hit = true;
		}
		else {
			m_transform.scale = m_hitTimer;
			m_transform.rotation += dt;
		}
	}
	else {
		m_transform.scale = max::Lerp(m_transform.scale,10.0f, 3.5f * dt);
		m_transform.rotation = max::randomf(max::Pi);
		if (m_transform.scale > 9.5f) {
			m_destroyed = true;
		}
	}
}

void Missile::OnCollision(Actor* other)
{
	//std::cout << "I have hit " << other->m_tag << std::endl;
}