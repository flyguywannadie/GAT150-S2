#include "GameTrack.h"
#include "Squisher.h"
#include "Frame/Scene.h"
#include "Spawner.h"
#include "Renderer/Renderer.h"
#include "Frame/Resource/ResourceManager.h"
#include "Frame/Component/ModelRenderComponent.h"
#include "Frame/Component/CircleCollisionComponent.h"
#include "Destroyer.h"
//#include "Core/Color.h"

bool GameTrack::Initialize() 
{
	StartWave();

	std::unique_ptr<Destroyer> destroyer = std::make_unique<Destroyer>(max::Transform{ GetPoint((int)m_model->GetPoints().size()-1),0,1});
	destroyer->m_tag = "Destroyer";
	destroyer->m_game = this->m_game;

	std::unique_ptr<max::ModelRenderComponent> component = std::make_unique<max::ModelRenderComponent>();
	component->m_model = max::g_resourceManager.Get<max::Model>("track1.txt", max::g_renderer);
	destroyer->AddComponent(std::move(component));

	std::unique_ptr<max::CircleCollisionComponent> collisionComponent = std::make_unique<max::CircleCollisionComponent>();
	collisionComponent->m_radius = 20.0f;
	destroyer->AddComponent(std::move(collisionComponent));

	m_scene->Add(std::move(destroyer));

	return true;
}

void GameTrack::StartWave() {
	std::vector<max::vec2> wave;
	//std::cout << m_game << std::endl;
	
	switch (dynamic_cast<Squisher*>(m_game)->m_currentWave) {
	case 1:
		wave = { {0.0f, 3.0f}, {0.0f, 3.0f}, {0.0f, 2.5f}, {1.0f, 2.5f}, {0.0f, 0.5f}, {0.0f, 1.0f}, {0.0f, 3.0f}, {0.0f, 0.5f} };
		break;
	case 2:
		wave = { {0.0f, 0.4f}, {0.0f, 0.2f},{0.0f, 0.6f},{0.0f, 0.4f}, {0.0f, 0.2f},{0.0f, 0.6f},{0.0f, 0.4f}, {0.0f, 0.2f},{0.0f, 0.6f},{0.0f, 0.4f}, {0.0f, 0.2f},{0.0f, 5.0f}, {2.0f, 0.5f} };
		break;
	case 3:
		wave = { {1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)},{1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)}, {1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)}, {1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)}, {1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)}, {1.0f, 0.1f} ,{0.0f, max::randomf(1.5f, 1.3f)},{0.0f, max::randomf(1.5f, 1.3f)},{0.0f, max::randomf(1.5f, 1.3f)},{0.0f, max::randomf(1.5f, 1.3f)} };
		break;
	case 4:
		wave = { {3.0f, 10.0f}, {2.0f, 0.5f} };
		break;
	case 5:
		wave = { {2.0f, 0.5f} , {0.0f, 0.5f}, {2.0f, 0.5f}, {0.0f, 0.5f}, {2.0f, 0.5f}, {0.0f, 0.5f} , {2.0f, 0.5f}, {0.0f, 0.5f} };
		break;
	case 6:
		wave = { {1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.0f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.0f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.0f}, {2.0f, 0.0f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.0f},{3.0f, 0.0f} };
		break;
	case 7:
		wave = { {3.0f, 3.0f}, {3.0f, 3.0f} , {3.0f, 3.0f} ,{3.0f, 1.5f}, {1.0f, 1.5f}, {3.0f, 3.0f} , {3.0f, 3.0f}, {1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 0.5f},{1.0f, 15.0f}, {2.0f, 2.0f} };
		break;
	}

	std::unique_ptr<Spawner> spawner = std::make_unique<Spawner>(max::Transform{ {m_transform.position + (m_model->GetPoints()[0] * m_transform.scale)},0,1 }, wave);
	spawner->m_tag = "Spawner";
	spawner->m_game = this->m_game;
	spawner->m_track = this;

	std::unique_ptr<max::ModelRenderComponent> component = std::make_unique<max::ModelRenderComponent>();
	component->m_model = max::g_resourceManager.Get<max::Model>("track1.txt", max::g_renderer);
	spawner->AddComponent(std::move(component));

	m_scene->Add(std::move(spawner));
}

void GameTrack::Update(float dt)
{
	Actor::Update(dt);

	if (dynamic_cast<Squisher*>(m_game)->m_currentWave > dynamic_cast<Squisher*>(m_game)->m_finalWave) {
		m_destroyed = true;
	}
}

void GameTrack::Draw(max::Renderer& renderer) {
	if (m_model->GetPoints().empty()) {
		return;
	}

	renderer.SetColor(max::Color::ToInt(m_model->GetColor().r), max::Color::ToInt(m_model->GetColor().g), max::Color::ToInt(m_model->GetColor().b), max::Color::ToInt(m_model->GetColor().a));

	for (int i = 0; i < m_model->GetPoints().size(); i++) {
		max::vec2 p1, p2;
		if (i + 1 < m_model->GetPoints().size()) {
			p1 = (m_model->GetPoints()[i] * m_transform.scale).Rotate(m_transform.rotation) + m_transform.position;
			p2 = (m_model->GetPoints()[i + 1] * m_transform.scale).Rotate(m_transform.rotation) + m_transform.position;
		}
		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void GameTrack::OnCollision(Actor* other)
{

}