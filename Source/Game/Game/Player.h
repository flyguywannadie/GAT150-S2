#pragma once
#include "Frame/Actor.h"

class Player : public max::Actor {
public:
	Player(float speed, float turnRate, const max::Transform& transform, std::shared_ptr<max::Model> model) :
		max::Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_health = 10;
	};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	int m_health = 0;

	float m_grounded = 3.0f;
	float m_jumping = 5.0f;

	float m_moveTimer = 0.2f; // time left till movement
	float m_moveTime = 0.2f; 
	float m_moveDistance = 12; // The distance it will travel per movement action
	int moveanim = 1;
	max::vec2 m_moveDir{0,0};
};