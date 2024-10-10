
#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/Component.h>
#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/TransformData.h>

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

Scene* Entity::GetScene() const
{
	return m_entity->ownScene;
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
