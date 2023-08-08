#include "Spawner.h"
#include "Squisher.h"
#include "Slug.h"
#include "Beetle.h"
#include "BigBeetle.h"
#include "Renderer/ModelManager.h"
#include "Frame/Scene.h"

void Spawner::Update(float dt)
{
	Actor::Update(dt);
	
	if (currentSpawn < m_spawns.size()) {
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0) {
			m_spawnTimer = m_spawns[currentSpawn].y;
			std::unique_ptr<Enemy> enemy;
			switch ((int)m_spawns[currentSpawn].x) {
			case 0:
				enemy = std::make_unique<Slug>(max::randomf(75.0f, 100.0f), 1000, 5, max::Transform{{m_transform.position}, 0, 1.5f});
				break;
			case 1:
				enemy = std::make_unique<Beetle>(50.0f, 6000, 0, max::Transform{ {m_transform.position}, 0, 2.0f });
				break;
			case 2:
				enemy = std::make_unique<Slug>(250.0f, 1000, 10, max::Transform{ {m_transform.position}, 0, 0.5f });
				break;
			case 3:
				enemy = std::make_unique<BigBeetle>(25.0f, 1000000, 25, max::Transform{ {m_transform.position}, 0, 3.0f });
				break;
			}
			enemy->m_tag = "Enemy";
			enemy->m_game = this->m_game;
			enemy->m_track = this->m_track;
			enemy->m_spawner = this;
			m_scene->Add(move(enemy));

			currentSpawn++;
		}
	}

	if (currentSpawn >= m_spawns.size() && m_enemiesKilled >= m_spawns.size()) {
		dynamic_cast<Squisher*>(m_game)->m_tracksDone++;
		m_destroyed = true;
	}
}

void Spawner::OnCollision(Actor* other)
{

}