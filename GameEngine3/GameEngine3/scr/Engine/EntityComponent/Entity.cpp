
#include <EntityComponent/Entity.h>

#include <EntityComponent/Component.h>
#include <EntityComponent/Scene.h>
#include <EntityComponent/TransformData.h>

struct Entity::Internal
{
	Scene* ownScene;
	std::unordered_map<const char*, Component*> components;
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
	m_entity->components[comp->GetType()] = comp;
	return m_entity->components[comp->GetType()];
}
Component* Entity::GetComponent(Component* comp)
{
	return m_entity->components[comp->GetType()];
}

void Entity::Render(Renderer* render)
{
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
void Entity::Update()
{
	for (auto& [key, comp] : m_entity->components) {
		comp->Update();
	}
}
