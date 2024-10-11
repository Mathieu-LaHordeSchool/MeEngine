
#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/RendererObject/Renderer.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/Timer/HandleTimer.h>

#include <map>
#include <vector>

struct Scene::Internal
{
	std::map<Entity*, std::vector<Entity*>> entitys;
	HandleTimer handleTimer;
};

Scene::Scene()
	: m_scene(new Internal())
{}

Entity* Scene::CreateObject(const char* name, TransformData* parent /* = nullptr */)
{
	Entity* newEntity = new Entity(this);
	m_scene->entitys[parent ? parent->GetOwner() : nullptr].push_back(newEntity);

	newEntity->Transform()->SetName(name);
	newEntity->Transform()->SetParent(parent);
	newEntity->Transform()->SetOwner(newEntity);

	return newEntity;
}

HandleTimer Scene::GetHandleTimer() const
{
	return m_scene->handleTimer;
}

void Scene::Start()
{
	LoopOnEntity([this](auto e) {
		e->Start();
	});
}
void Scene::BindInput(Inputs* inputs)
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
}
void Scene::Render(Renderer* render)
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
				func(entity);
				recursive(entity);
			}
		}
	};

	recursive(nullptr);
}
