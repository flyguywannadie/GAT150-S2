#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Frame/Component/CameraComponent.h"
#include "Frame/Component/Box2DPhysicsComponent.h"
#include "Frame/Component/BoxCollisionComponent.h"
#include "Frame/Component/SpriteAnimComponent.h"
#include "Frame/Component/Component.h"

namespace max
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_health = 10;

		//speed = 0;

		//CameraComponent::Instance().m_owner = this;

		transform.position = vec2{random(g_renderer.GetWidth()),random(g_renderer.GetHeight()) };

		m_physicsComponent = GetComponent<max::PhysicsComponent>();

		return false;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		Player* player = m_scene->GetActor<Player>();
		if (player) {
			max::Vector2 direction = player->transform.position - transform.position;
			transform.rotation = direction.Angle();
		}

		max::vec2 forward = max::vec2{ 1,0 }.Rotate(transform.rotation);
		//transform.position += (forward * speed) * max::g_time.GetDeltaTime();
		//transform.position.x = max::Wrap(transform.position.x, (float)max::g_renderer.GetWidth());
		//transform.position.y = max::Wrap(transform.position.y, (float)max::g_renderer.GetHeight());

		if (!grabbed) {
			m_physicsComponent->SetVelocity(forward * speed);
		}
		else {
			if (m_player) {
				m_physicsComponent->SetVelocity(max::vec2{ 2,0 }.Rotate((m_player->GetComponent<Box2DPhysicsComponent>()->m_velocity * max::vec2{ 1.25f,1.25f }).Angle()));
			}

			auto walls = m_scene->GetActorByName("Walls")->GetComponent<ModelRenderComponent>();
			if (walls) {
				if (!walls->IsInside(transform.position)) {
					max::EventManager::Instance().DispatchEvent("AddPoints", 100);

					destroyed = true;

					max::EmitterData data;
					data.burst = true;
					data.burstCount = 300;
					data.spawnRate = 0;
					data.angle = 0;
					data.angleRange = max::Pi;
					data.lifetimeMin = 4.25f;
					data.lifetimeMin = 7.0f;
					data.speedMin = 150;
					data.speedMax = 250;
					data.damping = 0.25f;
					data.color = max::Color{ 1, 0, 0, 1 };
					max::Transform t{ max::vec2{ transform.position.x, transform.position.y } + (forward * 15), 0, 1 };
					auto emitter = std::make_unique<max::Emitter>(t, data);
					emitter->lifespan = 1.0f;
					m_scene->Add(std::move(emitter));
				}
			}
		}
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player") {
			m_player = dynamic_cast<max::Player*>(other);
			if (m_player && m_player->squishin) {
				grabbed = true;
			}
		}
	}

	void Enemy::OnCollisionExit(Actor* other) {
		if (other->tag == "Player" && !grabbed) {
			m_player = nullptr;
		}
	}


	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		m_health = 10;

		READ_DATA(value, speed);
	}
}