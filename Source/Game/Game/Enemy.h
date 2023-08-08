#pragma once
#include "Frame/Actor.h"
#include "GameTrack.h"
#include "Spawner.h"
#include "Frame/Emitter.h"
#include "Audio/AudioSystem.h"
#include "Squisher.h"
#include "Frame/Scene.h"

class Enemy : public max::Actor {
public:
	Enemy(float speed, int health, int fuelreward, const max::Transform& transform) :
		max::Actor{ transform},
		m_speed{ speed },
		m_health{ health },
		m_fuelReward{ fuelreward }
	{
		m_nextPoint = m_transform.position;
	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	GameTrack* m_track = nullptr;
	Spawner* m_spawner = nullptr;

	friend class Spawner;

protected:
	float m_speed = 0;
	int m_health = 0;
	int m_damage = 0;

	int m_fuelReward = 4;

	int m_lastPoint = 0;
	max::vec2 m_nextPoint{ 0,0 };
};
