#include "Model.h"
#include "Renderer.h"
#include "Game/Squisher.h"
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

		auto* player = Squisher::Instance().GetScene()->GetActor<Player>();

		vec2 p11 = p1 - player->transform.position;
		vec2 p21 = p2 - player->transform.position;

		if (player->InView(p11, p21)) {

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);

			std::cout << i << std::endl;

			// Arc length formula
			// Theta        arc
			//  360  = circumference

			// arc = (Theta/360) * Circumference

			// find the difference in arc length between camera view and point positions
			// that will be the x position on screen

			float walldistance = p11.Distance(0);
			float walldistance2 = p21.Distance(0);

			float viewAngleMax = max::RadToDeg(player->transform.rotation) + player->m_viewAngle;
			viewAngleMax = fmod(viewAngleMax, 180);
			float viewAngleMin = max::RadToDeg(player->transform.rotation) - player->m_viewAngle;
			viewAngleMin = fmod(viewAngleMin, 180);

			//std::cout << "Cam angle: " << viewAngleMin << " - " << viewAngleMax << std::endl;
			
			float arclengthCameraStartP1 = (viewAngleMax/360.0f) * (walldistance * 2.0f * max::Pi);
			float arclengthCameraEndP1 = (viewAngleMin/360.0f) * (walldistance * 2.0f * max::Pi);
			
			float pangle = atan2(p11.y, p11.x);
			pangle = fmod(pangle, max::Pi);
			float arclengthPoint1 = (pangle/max::TwoPi) * (walldistance * 2.0f * max::Pi);

			//std::cout << "line angle 1: " << pangle << std::endl;

			float arclengthCameraStartP2 = ((player->transform.rotation + max::DegToRad(player->m_viewAngle)) / max::TwoPi) * (walldistance2 * 2.0f * max::Pi);
			float arclengthCameraEndP2 = ((player->transform.rotation - max::DegToRad(player->m_viewAngle)) / max::TwoPi) * (walldistance2 * 2.0f * max::Pi);

			pangle = atan2(p21.y, p21.x);
			pangle = fmod(pangle, max::Pi);
			float arclengthPoint2 = (pangle / max::TwoPi) * (walldistance2 * 2.0f * max::Pi);

			//std::cout << "line angle 2: " << pangle << std::endl;

			p1.x = renderer.GetWidth() - (renderer.GetWidth() * ((arclengthPoint1 - arclengthCameraStartP1) / (arclengthCameraEndP1 - arclengthCameraStartP1)));
			p2.x = renderer.GetWidth() - (renderer.GetWidth() * ((arclengthPoint2 - arclengthCameraStartP2) / (arclengthCameraEndP2 - arclengthCameraStartP2)));

			// find the distance from the player .
			// some ratio of that would determine how high and low the line is drawn on screen.

			float windowheight = renderer.GetHeight();
			float wallheight = 15.0f;
			float viewheightp1 = (tanf(player->m_viewAngle) * (walldistance));
			float viewheightp2 = (tanf(player->m_viewAngle) * (walldistance2));

			p1.y = (windowheight / 2) - ((wallheight / abs(viewheightp1)) * (windowheight / 2));
			p2.y = (windowheight / 2) - ((wallheight / abs(viewheightp2)) * (windowheight / 2));

			//renderer.DrawLine(p1.x, p1.y, p2.x, p2.y); // top line

			float bottomp1y = ((windowheight) - p1.y);
			float bottomp2y = ((windowheight) - p2.y);

			//renderer.DrawLine(p1.x, bottomp1y, p2.x, bottomp2y); // bottom line
			//renderer.DrawLine(p2.x, p2.y, p2.x, bottomp2y); // vertical line
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