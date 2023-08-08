#pragma once


namespace max
{
	class Component {
	public:
		virtual void Update(float dt) = 0;
	public:
		class Actor* m_owner = nullptr;
	};
}