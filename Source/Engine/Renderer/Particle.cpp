#include "Particle.h"
#include "Renderer.h"
#include "Frame/Component/CameraComponent.h"
#include "Frame/Actor.h"

namespace max
{
	void Particle::Update(float dt)
	{
		m_data.lifetimer += dt;
		if (m_data.lifetimer >= m_data.lifetime)
		{
			m_isActive = false;
			return;
		}
		m_data.prevPosition = m_data.position;
		m_data.position += m_data.velocity * dt;
		m_data.velocity *= std::pow(1.0f - m_data.damping, dt);
	}

	void Particle::Draw(Renderer& renderer)
	{
		renderer.SetColor(Color::ToInt(m_data.color.r), Color::ToInt(m_data.color.g), Color::ToInt(m_data.color.b), Color::ToInt(m_data.color.a));
		if (CameraComponent::Instance().m_owner) {
			auto* camera = &CameraComponent::Instance();
			auto* player = camera->m_owner;

			vec2 p1 = m_data.position;
			vec2 p2 = m_data.prevPosition;

			vec2 p11 = p1 - player->transform.position;
			vec2 p21 = p2 - player->transform.position;

			if (camera->InView(p11, p21)) {

				float walldistance = p11.Distance(0);
				float walldistance2 = p21.Distance(0);

				if (walldistance > 0 && walldistance2> 0) {
					vec2 forward = max::vec2{ 1,0 }.Rotate(player->transform.rotation);
					float viewRotation = forward.Angle();

					float viewAngleMax = viewRotation + max::DegToRad(camera->m_viewAngle);
					float viewAngleMin = viewRotation - max::DegToRad(camera->m_viewAngle);

					float arclengthCameraStartP1, arclengthCameraEndP1, arclengthCameraStartP2, arclengthCameraEndP2, arclengthPoint1, arclengthPoint2, p1angle, p2angle;

					arclengthCameraStartP1 = (viewAngleMax / TwoPi) * (walldistance * 2.0f * max::Pi);
					arclengthCameraEndP1 = (viewAngleMin / TwoPi) * (walldistance * 2.0f * max::Pi);

					arclengthCameraStartP2 = (viewAngleMax / TwoPi) * (walldistance2 * 2.0f * max::Pi);
					arclengthCameraEndP2 = (viewAngleMin / TwoPi) * (walldistance2 * 2.0f * max::Pi);

					p1angle = atan2(p11.y, p11.x);
					p2angle = atan2(p21.y, p21.x);


					if (viewRotation > HalfPi) {
						if (p1angle < 0) {
							p1angle += TwoPi;
						}
						if (p2angle < 0) {
							p2angle += TwoPi;
						}
					}
					else if (viewRotation < -HalfPi) {
						if (p1angle > 0) {
							p1angle -= TwoPi;
						}
						if (p2angle > 0) {
							p2angle -= TwoPi;
						}
					}

					arclengthPoint1 = (p1angle / max::TwoPi) * (walldistance * 2.0f * max::Pi);
					arclengthPoint2 = (p2angle / max::TwoPi) * (walldistance2 * 2.0f * max::Pi);

					float p1difference = (arclengthPoint1 - arclengthCameraStartP1);
					float p1camdifference = (arclengthCameraEndP1 - arclengthCameraStartP1);
					float p2difference = (arclengthPoint2 - arclengthCameraStartP2);
					float p2camdifference = (arclengthCameraEndP2 - arclengthCameraStartP2);

					p1.x = renderer.GetWidth() - (renderer.GetWidth() * (p1difference / p1camdifference));
					p2.x = renderer.GetWidth() - (renderer.GetWidth() * (p2difference / p2camdifference));

					float viewheightp1 = abs(tanf(camera->m_viewAngle * 2) * (walldistance));
					float viewheightp2 = abs(tanf(camera->m_viewAngle * 2) * (walldistance2));
					float wallheight = 35.0f;
					float windowheight = renderer.GetHeight();

					float test = windowheight + 1;
					float test2 = windowheight + 1;
					if (viewheightp1 >0.1f && viewheightp2 > 0.1f) {
						test = (windowheight / 2) + ((wallheight / viewheightp1)) * (windowheight / 2);
						test2 = (windowheight / 2) + ((wallheight / viewheightp2)) * (windowheight / 2);
					}


					p1.y = test;
					p2.y = test2;

					//renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
					renderer.DrawLine(p1.x, p1.y, p2.x, p2.y); // top line
				}
			}
		}
		else {

			renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
		}
	}
}