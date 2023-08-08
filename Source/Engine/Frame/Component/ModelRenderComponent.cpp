#include "ModelRenderComponent.h"
#include "Frame/Actor.h"
#include "Renderer/Renderer.h"

namespace max
{
	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
		// m_model->Draw(renderer, m_owner->
	}
}