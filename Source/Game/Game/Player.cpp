#include "Player.h"
#include "Input/InputSystem.h"
#include "Game/Squisher.h"
#include "Frame/Game.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "Enemy.h"
#include "Frame/Component/CameraComponent.h"

#include "Frame/framework.h"

namespace max {
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<max::PhysicsComponent>();
		m_modelRenderComponent = GetComponent<max::ModelRenderComponent>();

		CameraComponent::Instance().m_owner = this;

		auto collisionComponent = GetComponent<max::CollisionComponent>();

		if (collisionComponent) {

		}

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//transform.rotation = std::abs(fmod(transform.rotation, max::TwoPi));

		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			//transform.rotation -= max::DegToRad(1);
			m_physicsComponent->ApplyTorque(-1.5f * g_time.GetDeltaTime());
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			//transform.rotation += max::DegToRad(1);
			m_physicsComponent->ApplyTorque(1.5f * g_time.GetDeltaTime());
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !squishin) {
			//transform.position += max::vec2{ 1,0 }.Rotate(transform.rotation);
			m_physicsComponent->ApplyForce(max::vec2{ 1,0 }.Rotate(transform.rotation));
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && !squishin) {
			//transform.position += max::vec2{ -1,0 }.Rotate(transform.rotation);
			m_physicsComponent->ApplyForce(max::vec2{ -1,0 }.Rotate(transform.rotation));
		}

		//if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_K)) {
		//	auto enemy = INSTANTIATE(Enemy, "Enemy");
		//	enemy->transform.position = { 100, 100 };
		//	enemy->Initialize();
		//	m_scene->Add(std::move(enemy));
		//}

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE) && !squishin) {
			squishin = true;
		}
		else if (squishin) {
			m_physicsComponent->SetVelocity(max::vec2{ 5.5f,0.0f }.Rotate(transform.rotation));
			if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
				m_physicsComponent->SetTorque(0);
			}

			max::EmitterData data;
			data.burst = true;
			data.burstCount = 1;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = max::Pi;
			data.lifetimeMin = 10.5f;
			data.lifetimeMin = 10.5f;
			data.speedMin = 15;
			data.speedMax = 15;
			data.damping = 0.2f;
			data.color = max::Color{ 0.8, 0.5, 0.2, 1 };
			max::Transform t{ { transform.position.x, transform.position.y }, 0, 1 };
			auto emitter = std::make_unique<max::Emitter>(t, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}

		auto walls = m_scene->GetActorByName("Walls")->GetComponent<ModelRenderComponent>();
		if (walls) {
			if (!walls->IsInside(transform.position)) {
				m_physicsComponent->SetVelocity(0);
				if (squishin) {
					squishin = false;
					max::g_audioSystem.PlayOneShot("land", false);
					m_physicsComponent->SetVelocity(max::vec2{ -1,0 }.Rotate(transform.rotation) * 5);
					beinsqished = false;
				}
				else if (beinsqished) {
					CameraComponent::Instance().m_owner = nullptr;
					destroyed = true;
					Squisher::Instance().SetState(Squisher::eState::GameOver);
				}
			}
		}
		//transform.position.x = max::Wrap(transform.position.x, (float)max::g_renderer.GetWidth());
		//transform.position.y = max::Wrap(transform.position.y, (float)max::g_renderer.GetHeight());
	}

	void Player::Draw(max::Renderer& renderer) {
		Actor::Draw(renderer);

		if (CameraComponent::Instance().m_owner) {
			//renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation)).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation)).y);

			//renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation + max::DegToRad(CameraComponent::Instance().m_viewAngle))).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation + max::DegToRad(CameraComponent::Instance().m_viewAngle))).y);
			//renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation - max::DegToRad(CameraComponent::Instance().m_viewAngle))).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation - max::DegToRad(CameraComponent::Instance().m_viewAngle))).y);
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy" && !squishin) {
			beinsqished = true;
		}
	}
	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Enemy") {
			beinsqished = false;
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}