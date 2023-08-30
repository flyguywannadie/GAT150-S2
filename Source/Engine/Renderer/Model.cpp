#include "Model.h"
#include "Renderer.h"
//#include "Game/Squisher.h"
#include "Frame/Component/CameraComponent.h"
#include "Frame/Scene.h"
#include "Game/Player.h"
#include <sstream>

bool max::Model::Load(const std::string& filename)
{
	std::string buffer;
	max::readFile(filename, buffer);

	std::istringstream stream(buffer);

	stream >> m_color;

	std::string line;
	std::getline(stream, line);

	int numPoints = std::stoi(line);

	for (int i = 0; i < numPoints; i++) {
		vec2 point;

		stream >> point;

		m_points.push_back(point);
	}

	return true;
}

bool max::Model::Create(std::string filename, ...)
{
	return Load(filename);
}

void max::Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
{
	if (m_points.empty()) {
		return;
	}

	renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

	for (int i = 0; i < m_points.size(); i++) {
		vec2 p1, p2;
		if (i + 1 < m_points.size()) {
			p1 = (m_points[i] * scale).Rotate(rotation) + position;
			p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;
		}
		else {
			p1 = (m_points[i] * scale).Rotate(rotation) + position;
			p2 = (m_points[0] * scale).Rotate(rotation) + position;
		}
		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void max::Model::Draw(Renderer& renderer, const Transform& transform)
{
	if (m_points.empty()) {
		return;
	}

	mat3 mx = transform.GetMatrix();

	renderer.SetColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));

	for (int i = 0; i < m_points.size(); i++) {
		vec2 p1, p2;

		if (i + 1 < m_points.size()) {
			p1 = (mx * m_points[i]);
			p2 = (mx * m_points[i + 1]);
		}
		else {
			//p1 = (mx * m_points[i]);
			//p2 = (mx * m_points[0]);
		}

		if (CameraComponent::Instance().m_owner) {
			auto* camera = &CameraComponent::Instance();
			auto* player = camera->m_owner;

			vec2 p11 = p1 - player->transform.position;
			vec2 p21 = p2 - player->transform.position;

			if (camera->InView(p11, p21)) {

				renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);

				// Arc length formula
				// Theta        arc
				//  360  = circumference

				// arc = (Theta/360) * Circumference

				// find the difference in arc length between camera view and point positions
				// that will be the x position on screen

				float walldistance = p11.Distance(0);
				float walldistance2 = p21.Distance(0);

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

				if (p2angle < 0 && viewRotation > HalfPi) {
					p2angle += TwoPi;
				}
				if (p2angle > 0 && viewRotation < -HalfPi) {
					p2angle -= TwoPi;
				}
				if (p1angle < 0 && viewRotation > HalfPi) {
					p1angle += TwoPi;
				}
				if (p1angle > 0 && viewRotation < -HalfPi) {
					p1angle -= TwoPi;
				}

				arclengthPoint1 = (p1angle / max::TwoPi) * (walldistance * 2.0f * max::Pi);
				arclengthPoint2 = (p2angle / max::TwoPi) * (walldistance2 * 2.0f * max::Pi);

				float p1difference = (arclengthPoint1 - arclengthCameraStartP1);
				float p1camdifference = (arclengthCameraEndP1 - arclengthCameraStartP1);
				float p2difference = (arclengthPoint2 - arclengthCameraStartP2);
				float p2camdifference = (arclengthCameraEndP2 - arclengthCameraStartP2);

				
				p1.x = renderer.GetWidth() - (renderer.GetWidth() * (p1difference / p1camdifference));
				p2.x = renderer.GetWidth() - (renderer.GetWidth() * (p2difference / p2camdifference));

				// find the distance from the player .
				// some ratio of that would determine how high and low the line is drawn on screen.

				float windowheight = renderer.GetHeight();
				float wallheight = 15.0f;
				float viewheightp1 = (tanf(camera->m_viewAngle) * (walldistance));
				float viewheightp2 = (tanf(camera->m_viewAngle) * (walldistance2));

				p1.y = (windowheight / 2) - ((wallheight / abs(viewheightp1)) * (windowheight / 2));
				p2.y = (windowheight / 2) - ((wallheight / abs(viewheightp2)) * (windowheight / 2));

				renderer.DrawLine(p1.x, p1.y, p2.x, p2.y); // top line

				float bottomp1y = ((windowheight)-p1.y);
				float bottomp2y = ((windowheight)-p2.y);

				renderer.DrawLine(p1.x, bottomp1y, p2.x, bottomp2y); // bottom line
				renderer.DrawLine(p2.x, p2.y, p2.x, bottomp2y); // vertical line
			}
		}
		else {
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
		
}

float max::Model::GetRadius()
{
	if (m_radius != 0.0f) {
		return m_radius;
	}

	for (auto point : m_points) {
		float length = point.Length();
		m_radius = Max(m_radius, length);
	}

	return m_radius;
}