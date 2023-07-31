#include "Lazer.h"
#include "Input/InputSystem.h"
#include "Frame/Scene.h"
#include "Frame/Emitter.h"
#include "Squisher.h"

void Lazer::OnCreate() 
{
	dynamic_cast<Squisher*>(m_game)->SetFuelTimer(0.1f);
	dynamic_cast<Squisher*>(m_game)->m_fuel--;
}

void Lazer::Update(float dt)
{
	Actor::Update(dt);

	if (dynamic_cast<Squisher*>(m_game)->m_fuel > 0) {
		dynamic_cast<Squisher*>(m_game)->SetFuelTimer(dynamic_cast<Squisher*>(m_game)->GetFuelTimer() - dt);
		if (dynamic_cast<Squisher*>(m_game)->GetFuelTimer() <= 0) {
			dynamic_cast<Squisher*>(m_game)->SetFuelTimer(0.1f);
			dynamic_cast<Squisher*>(m_game)->m_fuel--;
		}
	}

	if (dynamic_cast<Squisher*>(m_game)->m_fuel > 0) 
	{
		max::vec2 direction = max::g_inputSystem.GetMousePosition() - m_transform.position;
		m_transform.position += direction * speed * max::g_time.GetDeltaTime();

		max::EmitterData data;
		data.burst = true;
		data.burstCount = 10;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = max::Pi;
		data.lifetimeMin = 0.25f;
		data.lifetimeMin = 0.5f;
		data.speedMin = 0;
		data.speedMax = 5;
		data.damping = 0.5f;
		data.color = max::Color{ 1, 0, 0, 1 };
		max::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<max::Emitter>(transform, data);
		emitter->m_lifespan = 0.4f;
		emitter->m_tag = "Red_Hot";
		m_scene->Add(std::move(emitter));

		m_transform.rotation = max::randomf(max::Pi);
		m_transform.scale = max::randomf(2, 1);
	}

	if (!max::g_inputSystem.GetMouseButtonDown(0) || dynamic_cast<Squisher*>(m_game)->m_fuel <= 0) {
		m_destroyed = true;
	}
}

void Lazer::OnCollision(Actor* other)
{
	//std::cout << "I have hit " << other->m_tag << std::endl;
}