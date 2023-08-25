#include "Blaster.h"

#include "Core/Logger.h"

#include "Frame/framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"

bool Blaster::Initialize()
{
	// Load Audio
	max::g_audioSystem.AddAudio("hit", "hit.wav");
	max::g_audioSystem.AddAudio("land", "land.wav");

	// Load Scene, Player, and Enemies
	m_scene = std::make_unique<max::Scene>();
	m_scene->Load("scenes/pscene.json");
	m_scene->Initialize();

	//for (int i = 0; i < 10; i++) {
	//	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(max::randomf(75.0f, 200.0f), max::Pi, max::Transform{ {max::random(800), max::random(600)}, max::randomf(0, 360), 2 }, max::g_ModelManager.Get("ship.txt"));
	//	enemy->m_tag = "Weapon";
	//	scene.Add(move(enemy));
	//}


	// add Events
	EVENT_SUBSCRIBE("AddPoints", Blaster::AddPoints);
	EVENT_SUBSCRIBE("PlayerDead", Blaster::OnPlayerDead);
	//max::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&Squisher::AddPoints, this, std::placeholders::_1));
	//max::EventManager::Instance().Subscribe("PlayerDead", this, std::bind(&Squisher::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void Blaster::Shutdown()
{
	m_scene->RemoveAll();
}

void Blaster::Update(float dt)
{
	switch (m_state)
	{
	case Blaster::eState::Title:
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_state = eState::TrackSelect;
			m_scene->GetActorByName("Background")->active = false;
			m_scene->GetActorByName("Title")->active = false;
		}
		break;
	case Blaster::eState::TrackSelect:
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case Blaster::eState::StartGame:
		m_baseHealth = 10;
		m_state = eState::StartLevel;
		break;
	case Blaster::eState::StartLevel:
		INFO_LOG("START LEVEL");
		m_scene->RemoveAll();
		
		m_state = eState::StartWave;
		break;
	case Blaster::eState::StartWave:
		m_state = eState::Game;
		break;
	case Blaster::eState::Game:

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_GRAVE)) {
			m_state = eState::GameOver;
		}

		if (m_fuel > 100) {
			m_fuel = 100;
		}
		if (m_fuel < 0) {
			m_fuel = 0;
		}

		if (m_baseHealth <= 0) {
			m_state = eState::GameOver;
			m_stateTimer = 3.0f;
		}

		break;
	case Blaster::eState::EndWave:

		break;
	case Blaster::eState::GameOver:
		m_scene->RemoveAll();
		m_stateTimer -= dt;
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_stateTimer = 0;
		}
		if (m_stateTimer <= 0) {
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	//"Left and Right Arrows Weapon:" + std::to_string(m_weaponSelect);
	//m_stageSelectText->Create(max::g_renderer, "A and D Key Stage: " + std::to_string(m_stageSelect), max::Color{1, 1, 1, 1});
	m_scene->Update(dt);
}


void Blaster::Draw(max::Renderer& renderer)
{
	m_scene->Draw(renderer);

	max::g_particleSystem.Draw(renderer);
}

void Blaster::AddPoints(const max::Event& event)
{

}

void Blaster::OnPlayerDead(const max::Event& event)
{

}
