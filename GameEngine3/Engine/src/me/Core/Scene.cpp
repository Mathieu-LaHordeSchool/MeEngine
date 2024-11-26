
#include <me/Core/Scene.h>
#include <me/Core/Entity.h>
#include <me/Core/TransformData.h>
#include <me/Core/Timer/HandleTimer.h>
#include <me/Render/Renderer.h>

#include <map>
#include <vector>
#include <algorithm>

using namespace me::core;

struct Scene::Internal
{
	std::map<Entity*, std::vector<Entity*>> entitys;

	me::core::timer::HandleTimer handleTimer;
	std::vector<Entity*> objectToDestroy;
};

Scene::Scene()
	: m_scene(new Internal())
{}

bool Scene::ContainsEntityWithName(Entity * parent, const char* name)
{
	auto vec = m_scene->entitys[parent];
	for (auto entity : vec)
	{
		if (entity->Transform()->GetName() == name)
			return true;
	}

	return false;
}

Entity* Scene::CreateObject(const char* name, TransformData* parent /* = nullptr */)
{
	Entity* parentOwner = parent ? parent->GetOwner() : nullptr;
	// if (ContainsEntityWithName(parentOwner, name))
	// 	return nullptr;

	Entity* newEntity = new Entity(this);
	m_scene->entitys[parentOwner].push_back(newEntity);

	newEntity->Transform()->SetName(name);
	newEntity->Transform()->SetParent(parent);
	newEntity->Transform()->SetOwner(newEntity);

	if (parent)
		parent->AddChildren(newEntity->Transform());

	return newEntity;
}
void Scene::Destroy(Entity* e)
{
	m_scene->objectToDestroy.push_back(e);
}

me::core::timer::HandleTimer Scene::GetHandleTimer() const
{
	return m_scene->handleTimer;
}

void Scene::Start()
{
	LoopOnEntity([this](auto e) {
		e->Start();
	});
}
void Scene::BindInput(me::core::input::Inputs* inputs)
{
	LoopOnEntity([this, &inputs](auto e) {
		e->BindInputs(inputs);
	});
}
void Scene::Update()
{
	UpdateTimer();

	LoopOnEntity([this](auto e) {
		e->Update();
	});

	DestroyVectorObject();
}
void Scene::Render(me::render::Renderer* render)
{
	render->ClearAllRendererData();

	LoopOnEntity([this, &render](auto e) {
		e->Render(render);
	});
}

void Scene::UpdateTimer()
{
	m_scene->handleTimer.Update();
}
void Scene::LoopOnEntity(std::function<void(Entity*)> func)
{
	std::function<void(Entity*)> recursive;
	recursive = [this, &recursive, &func](auto e) {
		if (m_scene->entitys.count(e)) {
			for (Entity* entity : m_scene->entitys[e]) {
				if (!entity->Transform()->GetActive())
					continue;

				func(entity);
				recursive(entity);
			}
		}
	};

	recursive(nullptr);
}
void Scene::DestroyVectorObject()
{
	for (auto& destroy : m_scene->objectToDestroy)
	{
		DestroyUniqueObject(destroy);
	}
}

void Scene::DestroyUniqueObject(Entity* obj)
{
	if (m_scene->entitys.count(obj)) {
		m_scene->entitys.erase(obj);
	}

	Entity* parent = nullptr;
	if (auto p = obj->Transform()->GetParent())
		parent = p->GetOwner();

	auto vec = m_scene->entitys[parent];
	auto it = std::find(vec.begin(), vec.end(), obj);

	if (it != vec.end()) {
		vec.erase(it);
	}
}
