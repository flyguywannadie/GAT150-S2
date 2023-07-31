#pragma once
#include "Frame/Actor.h"
#include "GameTrack.h"

class Spawner : public max::Actor {
public:
	Spawner(const max::Transform& transform, std::shared_ptr<max::Model> model, std::vector<max::vec2> spawns) :
		max::Actor{ transform, model },
		m_spawns{ spawns }
	{};
	~Spawner() {
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	friend class GameTrack;

	int m_enemiesKilled = 0;

	GameTrack* m_track = nullptr;

private:
	float m_spawnTimer = 0;

	std::vector<max::vec2> m_spawns;
	int currentSpawn = 0;
};