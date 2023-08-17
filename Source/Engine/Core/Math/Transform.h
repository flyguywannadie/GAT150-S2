#pragma once
#include "Core/Math/Vector2.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Core/Json.h"

namespace max
{
	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {};



		mat3 GetMatrix() const
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			
			return mt * ms * mr;
		}

		void Read(const json_t& value);
	};
}