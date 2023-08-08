#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace max {
	class ModelRenderComponent : public RenderComponent{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

	public:
		std::shared_ptr<Model> m_model;

	};
}