#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
//#include "Game/Squisher.h"
#include "Frame/Scene.h"
#include "Game/Player.h"
#include "Frame/Resource/ResourceManager.h"
#include "Frame/Component/CameraComponent.h"

namespace max {

	CLASS_DEFINITION(SpriteComponent);

	bool SpriteComponent::Initialize() {
		if (!textureName.empty()) {
 			m_texture = GET_RESOURCE(Texture, textureName, max::g_renderer);
		}
		if (source.w == 0 && source.h == 0) {
			if (m_texture) {
				source.x = 0;
				source.y = 0;
				source.w = (int)m_texture->GetSize().x;
				source.h = (int)m_texture->GetSize().y;
			}
		}

		return true;
	}

	void max::SpriteComponent::Update(float dt)
	{

	}

	void max::SpriteComponent::Draw(Renderer& renderer)
	{
		if (CameraComponent::Instance().m_owner) {
			auto* camera = &CameraComponent::Instance();
			auto* player = camera->m_owner;

			max::vec2 p1 = m_owner->transform.position - player->transform.position;

			if (camera->InView(p1)) {
				Transform t = m_owner->transform;



				renderer.DrawTexture(m_texture.get(), t);
			}
		}
		else {
			renderer.DrawTexture(m_texture.get(), source, m_owner->transform);
		}
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
		READ_DATA(value, source);
	}
}
