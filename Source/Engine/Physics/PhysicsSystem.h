#pragma once
#include "Frame/Singleton.h"
#include "box2d/include/box2d/box2d.h"
#include <memory>

namespace max
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);

		friend class Singleton;
		//<make singleton a friend class to access private constructor>
	private:
		PhysicsSystem() = default;
		//<declare default constructor>
	private:
		std::unique_ptr<b2World> m_world;
		//<unique pointer of b2World> m_world;
	};
}