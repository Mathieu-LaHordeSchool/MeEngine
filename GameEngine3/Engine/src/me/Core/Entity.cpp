
#include <iostream>

#include <me/Core/Entity.h>
#include <me/Core/Component.h>
#include <me/Core/Scene.h>
#include <me/Core/TransformData.h>

struct Entity::Internal
{
	Scene* ownScene;
	std::unordered_map<int, Component*> components;
	TransformData* transform = new TransformData();
};

Entity::Entity(Scene* scn)
	: m_entity(new Internal())
{
	m_entity->ownScene = scn;
}

TransformData* Entity::Transform()
{
	return m_entity->transform;
}

Component* Entity::AddComponent(Component* comp)
{
	int type = comp->GetType();
	m_entity->components[type] = comp;
	return m_entity->components[type];
}
Component* Entity::GetComponent(int comp)
{
	if (m_entity->components.count(comp) == 0)
		return nullptr;

	return m_entity->components[comp];
}
bool Entity::HasComponent(int comp)
{
	return m_entity->components.count(comp);
}

Scene* Entity::GetScene() const
{
	return m_entity->ownScene;
}

void Entity::Start()
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Start();
	}
}
void Entity::Render(Renderer* render)
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Render(render);
	}
}
void Entity::BindInputs(Inputs* inputs)
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->BindInputs(inputs);
	}
}
void Entity::Update()
{
	for (auto& [key, comp] : m_entity->components) {
		if (!comp->GetActive())
			continue;

		comp->Update();
	}
}