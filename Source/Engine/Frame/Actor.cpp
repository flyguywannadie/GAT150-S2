#include "Frame/Actor.h"
#include "Renderer/Renderer.h"
#include "Component/RenderComponent.h"

namespace max
{
	CLASS_DEFINITION(Actor)

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));

			AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f && !destroyed) {
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : components) {
			component->Update(dt);
		}
	}

	void Actor::Draw(max::Renderer& renderer)
	{
		//m_model->Draw(max::g_renderer, m_transform);

		for (auto& component : components)
		{
			RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent) {
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		//component->Initialize();
		components.push_back(std::move(component));
	}

	void Actor::Read(const rapidjson::Value& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistant);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) {
			transform.Read(GET_DATA(value, transform));
		}

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
			for (auto& componentValue : GET_DATA(value,components).GetArray()) {
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				component->m_owner = this;

				component->Initialize();
				AddComponent(std::move(component));
			}
		}
	}
}
