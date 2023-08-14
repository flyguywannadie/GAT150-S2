#pragma once
#include "Vector2.h"

namespace max {
	class Matrix2x2
	{
	public:
		vec2 rows[2];
		// [row][column]
		// rows[0] = vec2{ 0, 0 }
		// rows[1] = vec2{ 0, 0 }

		Matrix2x2() = default;
		Matrix2x2(const vec2& row1, const vec2& row2) {
			rows[0] = row1;
			rows[1] = row2;
		};

		vec2  operator [] (size_t index) const { return rows[index]; }
		vec2& operator [] (size_t index) { return rows[index]; }

		vec2 operator * (const vec2& v);
		Matrix2x2 operator * (const Matrix2x2& mx);

		static Matrix2x2 CreateScale(const vec2& scale);
		static Matrix2x2 CreateScale(float scale);
		static Matrix2x2 CreateRotation(float radians);

		static Matrix2x2 CreateIdentity();
	};

	inline vec2 max::Matrix2x2::operator*(const vec2& v)
	{
		// | a b |   | x |
		// | c d | * | y |

		vec2 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline Matrix2x2 Matrix2x2::operator*(const Matrix2x2& mx)
	{
		// | a b |   | e f |
		// | c d | * | g h |

		Matrix2x2 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];

		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix2x2 Matrix2x2::CreateIdentity() {
		return Matrix2x2{
			{ 1.0f, 0.0f},
			{ 0.0f, 1.0f}
		};
	}

	inline Matrix2x2 Matrix2x2::CreateScale(const vec2& scale)
	{
		return Matrix2x2{
			{ scale.x, 0.0f},
			{ 0.0f, scale.y}
		};
	}

	inline Matrix2x2 Matrix2x2::CreateScale(float scale)
	{
		return Matrix2x2{
			{ scale, 0.0f},
			{ 0.0f, scale}
		};
	}

	inline Matrix2x2 Matrix2x2::CreateRotation(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return Matrix2x2{
			{ c, -s},
			{ s, c}
		};
	}

	using mat2 = Matrix2x2;
}