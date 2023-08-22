#include "Walls.h"

bool Walls::Initialize()
{
	Actor::Initialize();

	return false;
}

void Walls::Update(float dt)
{
	Actor::Update(dt);

	//Component::Update(dt);

	//max::Vector2 direction = transform.position;
	//transform.rotation = direction.Angle() - 90.0f;

	//max::vec2 forward = max::vec2{ 0,1 }.Rotate(m_owner->transform.rotation);
	//transform.position += (forward * speed) * max::g_time.GetDeltaTime();
	//transform.position.x = max::Wrap(m_owner->transform.position.x, (float)max::g_renderer.GetWidth());
	//m_owner->transform.position.y = max::Wrap(m_owner->transform.position.y, (float)max::g_renderer.GetHeight());

}

void Walls::OnCollision(Actor* other)
{

}