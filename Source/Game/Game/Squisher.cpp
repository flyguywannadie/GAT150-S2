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

bool Squisher::Initialize()
{
	// Create Font/Text
	m_aeromaxfont = GET_RESOURCE(max::Font, "AEROMAX-Bold.ttf", 50);
	m_speedracerfont = GET_RESOURCE(max::Font, "RaceStripeDemoRegular.ttf", 50);
	m_orangejuicefont = GET_RESOURCE(max::Font, "orange juice 2.0.ttf", 30);
	m_mondeur = GET_RESOURCE(max::Font, "data-latin.ttf", 30);

	m_titleText = std::make_unique<max::Text>(m_speedracerfont);
	m_titleText->Create(max::g_renderer, "SQUISHER", max::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<max::Text>(m_speedracerfont);
	m_gameOverText->Create(max::g_renderer, "GAME OVER", max::Color{ 1, 1, 1, 1 });

	m_stageSelectText = std::make_unique<max::Text>(m_mondeur);

	m_healthText = std::make_unique<max::Text>(m_orangejuicefont);

	// Load Audio
	max::g_audioSystem.AddAudio("hit", "hit.wav");
	max::g_audioSystem.AddAudio("land", "land.wav");

	// Load Scene, Player, and Enemies
	m_scene = std::make_unique<max::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	//for (int i = 0; i < 10; i++) {
	//	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(max::randomf(75.0f, 200.0f), max::Pi, max::Transform{ {max::random(800), max::random(600)}, max::randomf(0, 360), 2 }, max::g_ModelManager.Get("ship.txt"));
	//	enemy->m_tag = "Weapon";
	//	scene.Add(move(enemy));
	//}

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
			m_state = eState::TrackSelect;
		}
		break;
	case Squisher::eState::TrackSelect:
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case Squisher::eState::StartGame:
		m_baseHealth = 10;
		m_state = eState::StartLevel;
		break;
	case Squisher::eState::StartLevel:
		INFO_LOG("START LEVEL");
		m_scene->RemoveAll();
		{
			// create player
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, max::Pi, max::Transform{ {313.289f,125.338f}, 1.11f, 1 });
			player->tag = "Player";
			player->m_game = this;

			auto component = CREATE_CLASS(ModelRenderComponent);
			component->m_model = GET_RESOURCE(max::Model, "box.txt", max::g_renderer);
			player->AddComponent(std::move(component));

			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			m_scene->Add(std::move(player));

			// create components
			//std::unique_ptr<max::SpriteComponent> component = std::make_unique<max::SpriteComponent>();
			//component->m_texture = max::g_resourceManager.Get<max::Texture>("blue-wooden-chair.png", max::g_renderer);
			//player->AddComponent(std::move(component));

			std::unique_ptr<Walls> walls = std::make_unique<Walls>(max::Transform{ {400, 300},0,30 });
			walls->tag = "Walls";
			walls->m_game = this;

			component = CREATE_CLASS(ModelRenderComponent);
			component->m_model = GET_RESOURCE(max::Model, "Walls.txt", max::g_renderer);
			walls->AddComponent(std::move(component));

			m_scene->Add(std::move(walls));
		}
		m_state = eState::StartWave;
		break;
	case Squisher::eState::StartWave:
		m_state = eState::Game;
		break;
	case Squisher::eState::Game:

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
	case Squisher::eState::EndWave:

		break;
	case Squisher::eState::GameOver:
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

	m_healthText->Create(max::g_renderer, "Base Health: " + std::to_string(m_baseHealth), max::Color{1, 1, 1, 1});
	m_scene->Update(dt);
}


void Squisher::Draw(max::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_titleText->Draw(max::g_renderer, 100, 300);
	}
	if (m_state == eState::Game || m_state == eState::EndWave) {
		m_healthText->Draw(max::g_renderer, 200, 500);
	}
	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(max::g_renderer, 100, 300);
	}
	if (m_state == eState::TrackSelect) {
		m_stageSelectText->Draw(max::g_renderer, 100, 100);
	}

	max::g_particleSystem.Draw(renderer);
	m_scene->Draw(renderer);
}
