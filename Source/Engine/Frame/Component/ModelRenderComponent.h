#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace max {
	class ModelRenderComponent : public RenderComponent{
	public:
		CLASS_DECLERATION(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }
		bool IsInside(const vec2& position);

	public:
		std::string modelName;
		std::shared_ptr<Model> m_model;

	};
}