#include "Player.h"
#include "Input/InputSystem.h"
#include "Squisher.h"
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
			m_physicsComponent->ApplyTorque(-1 * g_time.GetDeltaTime());
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			//transform.rotation += max::DegToRad(1);
			m_physicsComponent->ApplyTorque(1 * g_time.GetDeltaTime());
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) {
			//transform.position += max::vec2{ 1,0 }.Rotate(transform.rotation);
			m_physicsComponent->ApplyForce(max::vec2{ 1,0 }.Rotate(transform.rotation));
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) {
			//transform.position += max::vec2{ -1,0 }.Rotate(transform.rotation);
			m_physicsComponent->ApplyForce(max::vec2{ -1,0 }.Rotate(transform.rotation));
		}

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_K)) {
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform.position = { 100, 100 };
			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}


		if (tag == "Stomping") {
			tag = "Player";
		}

		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			transform.scale = max::Lerp(transform.scale, m_jumping, 3.5f * max::g_time.GetDeltaTime());

			if (transform.scale >= max::Lerp(m_grounded, m_jumping, 0.5)) {
				tag = "No";
			}
		}
		else if (max::g_inputSystem.GetKeyUpOnce(SDL_SCANCODE_SPACE)) {
			transform.scale = m_grounded;

			if (tag == "No") {
				tag = "Stomping";

				max::g_audioSystem.PlayOneShot("land", false);

				max::EmitterData data;
				data.burst = true;
				data.burstCount = 200;
				data.spawnRate = 0;
				data.angle = 0;
				data.angleRange = max::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMin = 0.5f;
				data.speedMin = 150;
				data.speedMax = 150;
				data.damping = 0.5f;
				data.color = max::Color{ 0.5, 0.5, 0.5, 1 };
				max::Transform t{ { transform.position.x, transform.position.y }, 0, 1 };
				auto emitter = std::make_unique<max::Emitter>(t, data);
				emitter->lifespan = 1.0f;
				m_scene->Add(std::move(emitter));
			}
			else {
				tag = "Player";
			}
		}

		//transform.position.x = max::Wrap(transform.position.x, (float)max::g_renderer.GetWidth());
		//transform.position.y = max::Wrap(transform.position.y, (float)max::g_renderer.GetHeight());
	}

	void Player::Draw(max::Renderer& renderer) {
		Actor::Draw(renderer);

		if (CameraComponent::Instance().m_owner) {
			renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation)).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation)).y);

			renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation + max::DegToRad(CameraComponent::Instance().m_viewAngle))).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation + max::DegToRad(CameraComponent::Instance().m_viewAngle))).y);
			renderer.DrawLine(transform.position.x, transform.position.y, (transform.position + max::vec2{ 1000,0 }.Rotate(transform.rotation - max::DegToRad(CameraComponent::Instance().m_viewAngle))).x, (transform.position + max::vec2{ 1000, 0 }.Rotate(transform.rotation - max::DegToRad(CameraComponent::Instance().m_viewAngle))).y);
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy_Bullet" && tag == "Player") {
			m_health--;
			if (m_health <= 0) {
				destroyed = true;

				max::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			}
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}