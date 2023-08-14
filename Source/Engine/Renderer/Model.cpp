#include "Model.h"
#include "Renderer.h"
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
			p1 = (mx * m_points[i]);
			p2 = (mx * m_points[0]);
		}
		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
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
