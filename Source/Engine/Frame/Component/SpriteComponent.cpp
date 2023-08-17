#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Frame/Actor.h"
#include "Frame/Resource/ResourceManager.h"

namespace max {

	CLASS_DEFINITION(SpriteComponent);

	bool SpriteComponent::Initialize() {
		m_texture = GET_RESOURCE(Texture, textureName);

		return true;
	}

	void max::SpriteComponent::Update(float dt)
	{

	}

	void max::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}
