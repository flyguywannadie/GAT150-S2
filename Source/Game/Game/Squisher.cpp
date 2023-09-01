#include "Squisher.h"
#include "Player.h"
#include "Enemy.h"
#include "Walls.h"

#include "Core/Logger.h"

#include "Frame/framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"

#include "Frame/Component/CameraComponent.h"

bool Squisher::Initialize()
{
	// Create Font/Text
	m_aeromaxfont = GET_RESOURCE(max::Font, "AEROMAX-Bold.ttf", 50);
	m_speedracerfont = GET_RESOURCE(max::Font, "RaceStripeDemoRegular.ttf", 50);
	m_orangejuicefont = GET_RESOURCE(max::Font, "orange juice 2.0.ttf", 30);
	m_mondeur = GET_RESOURCE(max::Font, "data-latin.ttf", 30);

	m_gameOverText = std::make_unique<max::Text>(m_speedracerfont);
	m_gameOverText->Create(max::g_renderer, "GAME OVER", max::Color{ 1, 1, 1, 1 });

	// Load Audio
	max::g_audioSystem.AddAudio("hit", "squisher/hit.wav");
	max::g_audioSystem.AddAudio("land", "squisher/land.wav");

	// Load Scene, Player, and Enemies
	m_scene = std::make_unique<max::Scene>();
	m_scene->Load("scenes/scene.json");
	m_scene->Initialize();

	//for (int i = 0; i < 10; i++) {
	//	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(max::randomf(75.0f, 200.0f), max::Pi, max::Transform{ {max::random(800), max::random(600)}, max::randomf(0, 360), 2 }, max::g_ModelManager.Get("ship.txt"));
	//	enemy->m_tag = "Weapon";
	//	scene.Add(move(enemy));
	//}


	// add Events
	EVENT_SUBSCRIBE("AddPoints", Squisher::AddPoints);
	EVENT_SUBSCRIBE("PlayerDead", Squisher::OnPlayerDead);
	//max::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&Squisher::AddPoints, this, std::placeholders::_1));
	//max::EventManager::Instance().Subscribe("PlayerDead", this, std::bind(&Squisher::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void Squisher::Shutdown()
{
	m_scene->RemoveAll();
}

void Squisher::Update(float dt)
{
	switch (m_state)
	{
	case Squisher::eState::Title:
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_scene->GetActorByName("Background")->active = false;
			m_scene->GetActorByName("Title")->active = false;
			m_state = eState::StartLevel1;
		}
		break;
	case Squisher::eState::StartLevel1:
		INFO_LOG("START LEVEL");
		m_scene->RemoveAll();
		{
			auto player = INSTANTIATE(Player, "Player");
			player->Initialize();
			m_scene->Add(std::move(player));

			auto walls = INSTANTIATE(Walls, "Walls");
			walls->transform.position = { 400, 300 };
			walls->Initialize();
			m_scene->Add(std::move(walls));
		}
		m_state = eState::Gaming;
		break;
	case Squisher::eState::Gaming:

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_GRAVE)) {
			m_state = eState::GameOver;
			max::CameraComponent::Instance().m_owner = nullptr;
		}

		break;
	case Squisher::eState::GameOver:
		m_scene->RemoveAll();
		m_stateTimer -= dt;
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_stateTimer = 0;
		}
		if (m_stateTimer <= 0) {
			m_state = eState::Title;
			m_scene->GetActorByName("Background")->active = true;
			m_scene->GetActorByName("Title")->active = true;
		}
		break;
	default:
		break;
	}

	//"Left and Right Arrows Weapon:" + std::to_string(m_weaponSelect);
	//m_stageSelectText->Create(max::g_renderer, "A and D Key Stage: " + std::to_string(m_stageSelect), max::Color{1, 1, 1, 1});
	m_scene->Update(dt);
}


void Squisher::Draw(max::Renderer& renderer)
{
	m_scene->Draw(renderer);

	max::g_particleSystem.Draw(renderer);

	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(max::g_renderer, 100, 300);
	}
}

void Squisher::AddPoints(const max::Event& event)
{
	
}

void Squisher::OnPlayerDead(const max::Event& event)
{
	
}
