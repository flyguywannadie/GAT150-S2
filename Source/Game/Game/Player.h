#pragma once
#include "Frame/Actor.h"
#include "Frame/Component/PhysicsComponent.h"
#include "Frame/Component/ModelRenderComponent.h"

class Player : public max::Actor {
public:
	Player(float speed, float turnRate, const max::Transform& transform) :
		max::Actor{ transform },
		speed{ speed },
		m_turnRate{ turnRate }
	{
		m_health = 10;
	};

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(max::Renderer& renderer) override;

	bool InView(max::vec2& point);
	bool InView(max::vec2& point1, max::vec2& point2);


private:
	float speed = 0;
	float m_turnRate = 0;
	int m_health = 0;

	float m_grounded = 3.0f;
	float m_jumping = 5.0f;

	float m_viewAngle = 25.0f;

	max::PhysicsComponent* m_physicsComponent = nullptr;
	max::ModelRenderComponent* m_modelRenderComponent = nullptr;
};