#include "Squisher.h"
#include "Player.h"
#include "Enemy.h"
#include "Lazer.h"
#include "Missile.h"
#include "GameTrack.h"

#include "Frame/framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"

bool Squisher::Initialize()
{
	// Create Font/Text
	m_aeromaxfont = max::g_resourceManager.Get<max::Font>("AEROMAX-Bold.ttf", 50);
	m_speedracerfont = max::g_resourceManager.Get<max::Font>("RaceStripeDemoRegular.ttf", 50);
	m_orangejuicefont = max::g_resourceManager.Get<max::Font>("orange juice 2.0.ttf", 30);
	m_mondeur = max::g_resourceManager.Get<max::Font>("data-latin.ttf", 30);

	m_titleText = std::make_unique<max::Text>(m_speedracerfont);
	m_titleText->Create(max::g_renderer, "SQUISHER", max::Color{ 1, 1, 1, 1 });

	m_scoreText = std::make_unique<max::Text>(m_orangejuicefont);

	m_gameOverText = std::make_unique<max::Text>(m_speedracerfont);
	m_gameOverText->Create(max::g_renderer, "GAME OVER", max::Color{ 1, 1, 1, 1 });

	m_lazerText = std::make_unique<max::Text>(m_orangejuicefont);

	m_stageSelectText = std::make_unique<max::Text>(m_mondeur);

	m_weaponSelectText = std::make_unique<max::Text>(m_mondeur);

	m_healthText = std::make_unique<max::Text>(m_orangejuicefont);

	// Load Audio
	max::g_audioSystem.AddAudio("hit", "hit.wav");
	max::g_audioSystem.AddAudio("land", "land.wav");

	// Load Scene, Player, and Enemies
	m_scene = std::make_unique<max::Scene>();

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
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_D)) {
			m_stageSelect += 1;
			if (m_stageSelect > m_totalTracks) {
				m_stageSelect = 1;
			}
		} else 	if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_A)) {
			m_stageSelect -= 1;
			if (m_stageSelect < 1) {
				m_stageSelect = m_totalTracks;
			}
		}
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_RIGHT)) {
			m_weaponSelect += 1;
			if (m_weaponSelect > 2) {
				m_weaponSelect = 1;
			}
		}
		else 	if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_LEFT)) {
			m_weaponSelect -= 1;
			if (m_weaponSelect < 1) {
				m_weaponSelect = 2;
			}
		}
		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case Squisher::eState::StartGame:
		m_currentWave = 1;
		m_baseHealth = 10;
		m_state = eState::StartLevel;
		break;
	case Squisher::eState::StartLevel:
		INFO_LOG("START LEVEL");
		m_scene->RemoveAll();
		{
			// create player
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, max::Pi, max::Transform{ {400,300}, 0, 3 });
			player->m_tag = "Player";
			player->m_game = this;

			std::unique_ptr<max::ModelRenderComponent> component = std::make_unique<max::ModelRenderComponent>();
			component->m_model = max::g_resourceManager.Get<max::Model>("box.txt", max::g_renderer);
			//component->m_texture = max::g_resourceManager.Get<max::Texture>("box1.png", max::g_renderer);
			player->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<max::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			m_scene->Add(std::move(player));

			// create components
			//std::unique_ptr<max::SpriteComponent> component = std::make_unique<max::SpriteComponent>();
			//component->m_texture = max::g_resourceManager.Get<max::Texture>("blue-wooden-chair.png", max::g_renderer);
			//player->AddComponent(std::move(component));
		}
		m_state = eState::StartWave;
		break;
	case Squisher::eState::StartWave:
		m_tracksDone = 0;
		if (m_stageSelect == 1) {
			std::unique_ptr<GameTrack> gametrack = std::make_unique<GameTrack>(max::Transform{ {400,300}, 0, 28.5 }, max::g_resourceManager.Get<max::Model>("track1.txt", max::g_renderer));
			gametrack->m_game = this;
			m_scene->Add(std::move(gametrack));
			m_trackCount = 1;
			m_finalWave = 4;
		}
		else {
			std::unique_ptr<GameTrack> gametrack = std::make_unique<GameTrack>(max::Transform{ {400,300}, 0, 28.5 }, max::g_resourceManager.Get<max::Model>("track2.txt", max::g_renderer));
			gametrack->m_game = this;
			m_scene->Add(std::move(gametrack));

			gametrack = std::make_unique<GameTrack>(max::Transform{ {400,300}, 0, 28.5 }, max::g_resourceManager.Get<max::Model>("track2a.txt", max::g_renderer));
			gametrack->m_game = this;
			m_scene->Add(std::move(gametrack));
			m_trackCount = 2;
			m_finalWave = 7;
		}
		//gametrack->StartWave();
		m_state = eState::Game;
		break;
	case Squisher::eState::Game:

		if (m_weaponTimer > 0) {
			m_weaponTimer -= dt;
		}

		if (max::g_inputSystem.GetKeyDownOnce(SDL_SCANCODE_GRAVE)) {
			m_state = eState::GameOver;
		}

		if (max::g_inputSystem.GetMouseButtonDownOnce(0) && m_fuel > 0 && m_weaponTimer <= 0) {
			switch (m_weaponSelect) {
			case 1:
			{
				std::unique_ptr<Lazer> lazer = std::make_unique<Lazer>(max::Transform{ {max::g_inputSystem.GetMousePosition()},0,0.05f });
				lazer->m_tag = "Lazer";
				lazer->m_game = this;

				std::unique_ptr<max::SpriteComponent> component = std::make_unique<max::SpriteComponent>();
				component->m_texture = max::g_resourceManager.Get<max::Texture>("blue-wooden-chair.png", max::g_renderer);
				lazer->AddComponent(std::move(component));

				m_scene->Add(std::move(lazer));
			}
				break;
			case 2:
			{
				std::unique_ptr<Missile> missile = std::make_unique<Missile>(max::Transform{ {max::g_inputSystem.GetMousePosition()},0,1 });
				missile->m_tag = "missile";
				missile->m_game = this;

				std::unique_ptr<max::SpriteComponent> component = std::make_unique<max::SpriteComponent>();
				component->m_texture = max::g_resourceManager.Get<max::Texture>("missile.png", max::g_renderer);
				missile->AddComponent(std::move(component));

				m_scene->Add(std::move(missile));
			}
				break;
			}

		}

		if (m_fuel > 100) {
			m_fuel = 100;
		}
		if (m_fuel < 0) {
			m_fuel = 0;
		}

		if (m_tracksDone == m_trackCount) {
			m_state = eState::EndWave;
			m_stateTimer = 3.0f;
		}

		if (m_baseHealth <= 0) {
			m_state = eState::GameOver;
			m_stateTimer = 3.0f;
		}

		break;
	case Squisher::eState::EndWave:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			if (m_currentWave < m_finalWave) {
				m_currentWave++;
				m_state = eState::StartWave;
			}
			else {
				m_scene->RemoveAll();
				m_state = eState::TrackSelect;
			}
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
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(max::g_renderer, "WAVE: " + std::to_string(m_currentWave) + "/" + std::to_string(m_finalWave), {1,1,1,1});
	m_lazerText->Create(max::g_renderer, "FUEL: " + std::to_string(m_fuel), max::Color{1, 1, 1, 1});
	//"Left and Right Arrows Weapon:" + std::to_string(m_weaponSelect);
	m_stageSelectText->Create(max::g_renderer, "A and D Key Stage: " + std::to_string(m_stageSelect), max::Color{1, 1, 1, 1});
	std::string weaponName = "";
	switch (m_weaponSelect) {
	case 1:
		weaponName = "Lazer";
		break;
	case 2:
		weaponName = "Missiles";
		break;
	}

	m_weaponSelectText->Create(max::g_renderer, "Leftand Right Arrows Weapon : " + weaponName, max::Color{1, 1, 1, 1});
	m_healthText->Create(max::g_renderer, "Base Health: " + std::to_string(m_baseHealth), max::Color{1, 1, 1, 1});
	m_scene->Update(dt);
}


void Squisher::Draw(max::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_titleText->Draw(max::g_renderer, 100, 300);
	}
	if (m_state == eState::Game || m_state == eState::EndWave) {
		m_scoreText->Draw(max::g_renderer, 100, 100);
		m_lazerText->Draw(max::g_renderer, 400, 500);
		m_healthText->Draw(max::g_renderer, 200, 500);
	}
	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(max::g_renderer, 100, 300);
	}
	if (m_state == eState::TrackSelect) {
		m_stageSelectText->Draw(max::g_renderer, 100, 100);
		m_weaponSelectText->Draw(max::g_renderer, 100, 200);
	}

	max::g_particleSystem.Draw(renderer);
	m_scene->Draw(renderer);
}
