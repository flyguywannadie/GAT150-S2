#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Game/Squisher.h"
#include "Frame/Scene.h"
#include "Game/Player.h"
#include "Frame/Resource/ResourceManager.h"

namespace max {

	CLASS_DEFINITION(SpriteComponent);

	bool SpriteComponent::Initialize() {
		if (!textureName.empty()) {
 			m_texture = GET_RESOURCE(Texture, textureName, max::g_renderer);
		}
		return true;
	}

	void max::SpriteComponent::Update(float dt)
	{

	}

	void max::SpriteComponent::Draw(Renderer& renderer)
	{
		Player* player = Squisher::Instance().GetScene()->GetActor<Player>();

		if (player) {
			max::vec2 p1 = m_owner->transform.position - player->transform.position;

			if (player->InView(p1)) {
				renderer.DrawTexture(m_texture.get(), m_owner->transform);
			}
		}
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}
