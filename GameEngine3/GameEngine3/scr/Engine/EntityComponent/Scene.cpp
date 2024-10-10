
#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/RendererObject/Renderer.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/Timer/HandleTimer.h>

struct Scene::Internal
{
	std::vector<Entity*> entitys;
	HandleTimer handleTimer;
};

Scene::Scene()
	: m_scene(new Internal())
{
}

Entity* Scene::CreateObject(const char* name, TransformData* parent /* = nullptr */)
{
	Entity* newEntity = new Entity(this);
	m_scene->entitys.push_back(newEntity);
	newEntity->Transform()->name = name;
	newEntity->Transform()->parent = parent;

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
void Scene::BindInput(Inputs* inputs)
{
	for (auto& e : m_scene->entitys) {
		e->BindInputs(inputs);
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
