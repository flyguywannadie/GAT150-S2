#pragma once
#include "Renderer/Texture.h"
#include "RenderComponent.h"
#include "Frame/Factory.h"

namespace max
{
	class SpriteComponent : public RenderComponent {
	public:
		CLASS_DECLERATION(SpriteComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }

	public:
		std::string textureName;
		res_t<Texture> m_texture;
	};
}