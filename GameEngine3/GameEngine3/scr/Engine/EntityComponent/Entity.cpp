
#include <iostream>

#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/Component.h>
#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/TransformData.h>

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

void Entity::Render(Renderer* render)
{
	// std::cout << m_entity->components.size() << std::endl;

	for (auto& [key, comp] : m_entity->components) {
		comp->Render(render);
	}
}

void Entity::Start()
{
	for (auto& [key, comp] : m_entity->components) {
		comp->Start();
	}
}
void Entity::BindInputs(Inputs* inputs)
{
	for (auto& [key, comp] : m_entity->components) {
		comp->BindInputs(inputs);
	}
}
void Entity::Update()
{
	for (auto& [key, comp] : m_entity->components) {
		comp->Update();
	}
}
