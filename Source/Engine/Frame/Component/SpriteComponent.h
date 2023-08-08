#pragma once
#include "Renderer/Texture.h"
#include "RenderComponent.h"

namespace max
{
	class SpriteComponent : public RenderComponent {
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

	public:
		res_t<Texture> m_texture;
	};
}