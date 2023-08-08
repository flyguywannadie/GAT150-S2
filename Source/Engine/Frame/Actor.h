#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Frame/Component/Component.h"

namespace max
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const max::Transform& transform) : m_transform{ transform } {};
		virtual ~Actor() {}

		virtual void Update(float dt);
		virtual void Draw(max::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() {
			return 30.0f;//(m_model) ? m_model->GetRadius() * m_transform.scale : (m_tag != "") ? 0 : -10000;
		}
		virtual void OnCollision(Actor* other) {}
		virtual void OnCreate();

		friend class Squisher;
		friend class Scene;
		friend class Lazer;

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

		max::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& actor : m_components) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}
}