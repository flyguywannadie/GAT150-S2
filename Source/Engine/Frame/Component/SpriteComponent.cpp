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
				Transform* t = &m_owner->transform;

				float walldistance = p1.Distance(0);

				vec2 forward = max::vec2{ 1,0 }.Rotate(player->transform.rotation);
				float viewRotation = forward.Angle();

				float viewAngleMax = viewRotation + max::DegToRad(camera->m_viewAngle);
				float viewAngleMin = viewRotation - max::DegToRad(camera->m_viewAngle);

				float p1angle = p1.Angle();
				float arclengthPoint1 = (p1angle / max::TwoPi) * (walldistance * 2.0f * max::Pi);

				float arclengthCameraStartP1 = (viewAngleMax / TwoPi) * (walldistance * 2.0f * max::Pi);
				float arclengthCameraEndP1 = (viewAngleMin / TwoPi) * (walldistance * 2.0f * max::Pi);

				float p1difference = (arclengthPoint1 - arclengthCameraStartP1);
				float p1camdifference = (arclengthCameraEndP1 - arclengthCameraStartP1);

				t->position.x = renderer.GetWidth() - (renderer.GetWidth() * (p1difference / p1camdifference));

				if (p1angle < 0 && viewRotation > 0) {
					p1angle += TwoPi;
				}
				if (p1angle > 0 && viewRotation < 0) {
					p1angle -= TwoPi;
				}

				t->position.y = g_renderer.GetHeight()/2;

				t->rotation = 0;

				float windowheight = renderer.GetHeight();
				float textureHeight = 1.0f;
				float viewheightp1 = (tanf(camera->m_viewAngle * 2) * (walldistance));
				t->scale = (textureHeight / abs(viewheightp1)) * (windowheight / 2);

				//std::cout << t->scale << std::endl;

				renderer.DrawTexture(m_texture.get(), source, *t);
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
