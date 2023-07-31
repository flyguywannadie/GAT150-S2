#include "Frame/Actor.h"
#include "Renderer/Renderer.h"

namespace max
{
	void Actor::OnCreate() {

	}

	void Actor::Update(float dt) 
	{
		if (m_lifespan != -1.0f && !m_destroyed) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);
	}

	void Actor::Draw(max::Renderer& renderer)
	{
		m_model->Draw(max::g_renderer, m_transform);
	}
}
