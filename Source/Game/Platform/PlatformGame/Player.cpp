#include "Player.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"

#include "Frame/framework.h"

namespace max {
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<max::PhysicsComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		float dir = 0;
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			dir = -1;
		}
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			dir = 1;
		}

		max::vec2 forward = max::vec2{ 1, 0 };

		m_physicsComponent->ApplyForce(forward * speed * dir);

		bool onGround = (groundCount > 0);

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE) && onGround) {
			max::vec2 up = max::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Ground") {
			groundCount++;
		}
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") {
			groundCount--;
		}
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}