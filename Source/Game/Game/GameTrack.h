#pragma once
#include "Frame/Actor.h"
#include "Core/Vector2.h"
#include "Renderer/Model.h"

class GameTrack : public max::Actor {
public:
	GameTrack(const max::Transform& transform, std::shared_ptr<max::Model> model) :
		max::Actor{ transform },
		m_model{ model }
	{};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void OnCreate() override;

	void Draw(max::Renderer& renderer) override;

	max::vec2 GetPoint(int num) const { return m_transform.position + (m_model->GetPoints()[num] * m_transform.scale); }
	void StartWave();

private:
	bool m_setup = false;

	std::shared_ptr<max::Model> m_model;
};