#pragma once
#include "Component.h"
#include "Frame/Singleton.h"

namespace max
{
	class CameraComponent : public Component, public Singleton<CameraComponent>
	{
	public:
		//CLASS_DECLERATION(CameraComponent);

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

		bool InView(max::vec2& point);
		bool InView(max::vec2& point1, max::vec2& point2);

		float m_viewAngle = 25.0f;

	private:
	};
}