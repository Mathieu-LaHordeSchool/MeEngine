
#include <EntityComponent/Scene.h>

#include <EntityComponent/Entity.h>
#include <RendererObject/Renderer.h>
#include <EntityComponent/TransformData.h>

#include <Timer/HandleTimer.h>

struct Scene::Internal
{
	std::vector<Entity*> entitys;
	HandleTimer handleTimer;
};

Scene::Scene()
	: m_scene(new Internal())
{
}

Entity* Scene::CreateObject(const char* name)
{
	Entity* newEntity = new Entity(this);
	m_scene->entitys.push_back(newEntity);
	newEntity->Transform()->name = name;

	return newEntity;
}

HandleTimer Scene::GetHandleTimer() const
{
	return m_scene->handleTimer;
}

void Scene::Start()
{
	for (auto& e : m_scene->entitys) {
		e->Start();
	}
}
void Scene::Update()
{
	UpdateTimer();

	for (auto& e : m_scene->entitys) {
		e->Update();
	}
}

void Scene::UpdateTimer()
{
	m_scene->handleTimer.Update();
}

void Scene::Render(Renderer* render)
{
	for (auto& e : m_scene->entitys) {
		e->Render(render);
	}
}
