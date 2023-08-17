#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Frame/Component/Component.h"

namespace max
{
	class Actor : public Object
	{
	public:
		CLASS_DECLERATION(Actor)

		Actor() = default;
		Actor(const max::Transform& transform) : transform{ transform } {};
		//virtual ~Actor() {}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(max::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() {
			return 30.0f;//(m_model) ? m_model->GetRadius() * m_transform.scale : (m_tag != "") ? 0 : -10000;
		}
		virtual void OnCollision(Actor* other) {}

		friend class Squisher;
		friend class Scene;

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;

	public:
		max::Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool destroyed = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& actor : components) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}
}