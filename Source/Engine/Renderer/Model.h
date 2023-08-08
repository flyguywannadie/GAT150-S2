#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include "Frame/Resource/Resource.h"
#include <vector>

namespace max
{
	class Model : public Resource
	{
	public:
		Model() = default;
		Model(std::vector<vec2>& points) : m_points{ points } {};

		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();
		std::vector<vec2> GetPoints() const { return m_points; }
		Color GetColor() const { return m_color; };

		virtual bool Create(std::string filename, ...) override;

	private:
		float m_radius = 0;
		std::vector<vec2> m_points;
		Color m_color;
	};
}