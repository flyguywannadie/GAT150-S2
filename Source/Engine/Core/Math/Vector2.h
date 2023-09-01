#pragma once
#include <sstream>
#include "Core/Math/MathUtils.h"

namespace max
{
	class Vector2
	{
	public:
		float x, y;
	public:
		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector2 operator - () const { return Vector2(-x,-y); }
		Vector2 Negate() const { return Vector2(-x, -y); }

		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
	
		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return sqrt(LengthSqr()); }

		float DistanceSqr(const Vector2& v) const { return (v - *this).LengthSqr(); }
		float Distance(const Vector2& v) const { return (v - *this).Length(); }

		Vector2 Normalized() { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		float Angle() const { return std::atan2f(y,x); }
		Vector2 Rotate(float radians) const;
		bool DoesLineIntersect(const Vector2& a, const Vector2& b, const Vector2& q, const Vector2& r);

		static float SignedAngle(const Vector2& v1, const Vector2& v2);
		static float Angle(const Vector2& v1, const Vector2& v2);
		static float Dot(const Vector2& v1, const Vector2& v2);

		
	};

	inline bool DoesLineIntersect(const Vector2& a, const Vector2& b, const Vector2& q, const Vector2& r) {
		//https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment
		auto x1 = a.x;
		auto y1 = a.y;
		auto x2 = b.x;
		auto y2 = b.y;
		auto x3 = q.x;
		auto y3 = q.y;
		auto x4 = r.x;
		auto y4 = r.y;
		auto tn = ((x1 - x3) * (y3 - y4)) -((y1 - y3) * (x3 - x4));
		auto td = ((x1 - x2) * (y3 - y4)) -((y1 - y2) * (x3 - x4));
		//FPE?
		if (td == 0.0f || std::abs(td) < std::abs(tn) || (tn != 0.0f && max::Sign(td) != max::Sign(tn))) return false;
		auto un = ((x1 - x3) * (y1 - y2)) - ((y1 - y3) * (x1 - x2));
		auto ud = td; //((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4))
		//FPE?
		if (ud == 0.0f || std::abs(ud) < std::abs(un) || (un != 0.0f && max::Sign(ud) != max::Sign(un))) return false;
		auto t = tn / td;
		//return Vec2(x1 + (t * (x2 - x1)), y1 + (t * (y2 - y1)))
		return true;
	}

	inline Vector2 Vector2::Rotate(float radians) const {
		float _x = (x * std::cos(radians)) - (y * std::sin(radians));
		float _y = (x * std::sin(radians)) + (y * std::cos(radians));

		return { _x, _y };
	}

	inline std::istream& operator >> (std::istream& stream, Vector2& v) {

		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	// get the unsigned angle in radians between the normalized v1 and normalized v2
	inline float Vector2::Angle(const Vector2& v1, const Vector2& v2)
	{
		return std::acos(Dot(v1, v2));
	}

	// get the signed counterclockwise angle in radians between v1 and v2
	inline float Vector2::SignedAngle(const Vector2& v1, const Vector2& v2)
	{
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return std::atan2(y, x);
	}

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector2::Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector2& v)
	{
		stream << v.x << " " << v.y;
		return stream;
	}

	using vec2 = Vector2;
}