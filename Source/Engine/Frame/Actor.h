#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace max
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const max::Transform& transform) : m_transform{ transform } {};
		Actor(const max::Transform transform, std::shared_ptr<Model> model) : m_transform{ transform }, m_model{ model } {};
		virtual ~Actor() {}

		virtual void Update(float dt);
		virtual void Draw(max::Renderer& renderer);

		float GetRadius() {
			return (m_model) ? m_model->GetRadius() * m_transform.scale : (m_tag != "") ? 0 : -10000;
		}
		virtual void OnCollision(Actor* other) {}
		virtual void OnCreate();

		void AddForce(const vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		friend class Squisher;
		friend class Scene;
		friend class Lazer;

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

		max::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false;

		std::shared_ptr<Model> m_model;

		max::vec2 m_velocity;
		float m_damping = 0.25;
	};
}