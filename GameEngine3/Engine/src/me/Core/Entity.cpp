
#include <iostream>

#include <me/Core/Entity.h>
#include <me/Core/Component.h>
#include <me/Core/Scene.h>
#include <me/Core/TransformData.h>

using namespace me::core;

struct me::core::Entity::Internal
{
	Scene* ownScene;
	std::unordered_map<const char*, Component*> components;

	TransformData* uiTransform = new TransformData();
	TransformData* transform = new TransformData();
};

me::core::Entity::Entity(Scene* scn)
	: m_entity(new Internal())
{
	m_entity->ownScene = scn;
}

TransformData* me::core::Entity::Transform() const
{
	return m_entity->transform;
}

Component* me::core::Entity::AddComponent(Component* comp)
{
	const char* type = comp->GetType();
	m_entity->components[type] = comp;
	return m_entity->components[type];
}

Component* me::core::Entity::GetComponent(const char* comp)
{
	if (m_entity->components.count(comp) == 0)
		return nullptr;

	return m_entity->components[comp];
}
bool me::core::Entity::HasComponent(const char* comp)
{
	return m_entity->components.count(comp);
}

Scene* me::core::Entity::GetScene() const
{
	return m_entity->ownScene;
}

void me::core::Entity::Start()
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Start();
	}
}
void me::core::Entity::Render(me::render::Renderer* render)
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Render(render);
	}
}
void me::core::Entity::BindInputs(me::core::input::Inputs* inputs)
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->BindInputs(inputs);
	}
}
void me::core::Entity::Update()
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Update();
	}
}
