#pragma once
#include "Frame/Object.h"

namespace max
{
	class Component : public Object {
	public:
		virtual void Update(float dt) = 0;

	public:
		class Actor* m_owner = nullptr;
	};
}