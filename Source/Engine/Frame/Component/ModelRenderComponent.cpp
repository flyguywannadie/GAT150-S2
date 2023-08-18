#include "ModelRenderComponent.h"
#include "Frame/Actor.h"
#include "Frame/Resource/ResourceManager.h"

namespace max
{
	CLASS_DEFINITION(ModelRenderComponent);

	bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty()) {
			m_model = GET_RESOURCE(Model, modelName);
		}
		return true;
	}

	void ModelRenderComponent::Update(float dt)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
		// m_model->Draw(renderer, m_owner->
	}

	void ModelRenderComponent::Read(const json_t& value) {
		READ_DATA(value, modelName);
	}
}