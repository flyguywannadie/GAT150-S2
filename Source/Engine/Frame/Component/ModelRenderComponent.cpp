#include "ModelRenderComponent.h"
#include "Frame/Actor.h"
#include "Frame/Resource/ResourceManager.h"
#include "CameraComponent.h"

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
		if (CameraComponent::Instance().m_owner) {
			//std::cout << IsInside(CameraComponent::Instance().m_owner->transform.position) << std::endl;
		}
	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
		// m_model->Draw(renderer, m_owner->
	}

	bool ModelRenderComponent::IsInside(const vec2& position)
	{
		int contacts = 0;

		mat3 mx = m_owner->transform.GetMatrix();
		
		auto m_points = m_model->GetPoints();

		for (int i = 0; i < m_points.size(); i++) {
			vec2 p1, p2;

			if (i + 1 < m_points.size()) {
				p1 = (mx * m_points[i]);
				p2 = (mx * m_points[i + 1]);
			}
			else {
				p1 = (mx * m_points[i]);
				p2 = (mx * m_points[0]);
			}

			if (DoesLineIntersect(p1, p2, position, position + vec2{ 100000,0 })) {
				contacts++;
			}
		}

		if (contacts % 2 == 1) {
			return true;
		} else {
			return false;
		}

	}

	void ModelRenderComponent::Read(const json_t& value) {
		READ_DATA(value, modelName);
	}
}