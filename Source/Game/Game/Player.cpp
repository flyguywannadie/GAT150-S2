#include "Player.h"
#include "Input/InputSystem.h"
#include "Squisher.h"
#include "Frame/Scene.h"
#include "Audio/AudioSystem.h"
#include "Frame/Emitter.h"
#include "Renderer/ModelManager.h"
#include "Frame/Component/ModelRenderComponent.h"
#include "Frame/Component/Component.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	if (m_moveDir.x == 0 && m_moveDir.y == 0) {
		if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) || max::g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) {
			m_moveDir.x = -1;
			m_transform.rotation = max::DegToRad(180);
		}
		else if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) || max::g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) {
			m_moveDir.x = 1;
			m_transform.rotation = max::DegToRad(0);
		}
		else if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) || max::g_inputSystem.GetKeyDown(SDL_SCANCODE_UP)) {
			m_moveDir.y = -1;
			m_transform.rotation = max::DegToRad(-90);
		}
		else if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) || max::g_inputSystem.GetKeyDown(SDL_SCANCODE_DOWN)) {
			m_moveDir.y = 1;
			m_transform.rotation = max::DegToRad(90);
		}
	}

	if (m_moveDir.x != 0 || m_moveDir.y != 0) {
		m_moveTimer -= dt;

		if (m_moveTimer <= 0) {
			m_moveTimer = m_moveTime;

			if (m_moveDir.x != 0) {
				m_transform.position.x = m_transform.position.x + (m_moveDir.x * m_moveDistance);
			}
			else {
				m_transform.position.y = m_transform.position.y + (m_moveDir.y * m_moveDistance);
			}

			moveanim++;
			if (moveanim > 4) {
				moveanim = 1;
				m_moveDir = { 0,0 };
				GetComponent<max::ModelRenderComponent>()->m_model = max::g_ModelManager.Get("box.txt");
			}
		}
	}

	

	switch (moveanim) {
	case (2):
		GetComponent<max::ModelRenderComponent>()->m_model = max::g_ModelManager.Get("boxmove1.txt");
		break;
	case (3):
		GetComponent<max::ModelRenderComponent>()->m_model = max::g_ModelManager.Get("boxmove2.txt");
		break;
	case (4):
		GetComponent<max::ModelRenderComponent>()->m_model = max::g_ModelManager.Get("boxmove3.txt");
		break;
	}

	if (m_tag == "Stomping") {
		m_tag = "Player";
	}

	if (max::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_transform.scale = max::Lerp(m_transform.scale, m_jumping, 3.5f * max::g_time.GetDeltaTime());

		if (m_transform.scale >= max::Lerp(m_grounded, m_jumping, 0.5)) {
			m_tag = "No";
		}
	}
	else if (max::g_inputSystem.GetKeyUpOnce(SDL_SCANCODE_SPACE)) {
		m_transform.scale = m_grounded;

		if (m_tag == "No") {
			m_tag = "Stomping";

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
			max::Transform transform{ { m_transform.position.x, m_transform.position.y }, 0, 1 };
			auto emitter = std::make_unique<max::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
		else {
			m_tag = "Player";
		}
	}

	m_transform.position.x = max::Wrap(m_transform.position.x, (float)max::g_renderer.GetWidth());
	m_transform.position.y = max::Wrap(m_transform.position.y, (float)max::g_renderer.GetHeight());
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy_Bullet" && m_tag == "Player") {
		m_health--;
		if (m_health <= 0) {
			m_destroyed = true;
		}
	}
}
