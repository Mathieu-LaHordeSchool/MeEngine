
#include <EntityComponent/Scene.h>

#include <EntityComponent/Entity.h>
#include <RendererObject/Renderer.h>
#include <EntityComponent/TransformData.h>

Entity* Scene::CreateObject(const char* name)
{
	Entity* newEntity = new Entity(this);
	entitys.push_back(newEntity);
	newEntity->Transform()->name = name;

	return newEntity;
}

void Scene::Render(Renderer* render)
{
	for (auto& e : entitys) {
		e->Render(render);
	}
}
