#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Frame/Actor.h"

namespace max {
	void max::SpriteComponent::Update(float dt)
	{

	}

	void max::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, RadToDeg(m_owner->m_transform.rotation));
	}
}
