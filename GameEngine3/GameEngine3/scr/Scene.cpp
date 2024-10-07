
#include <EntityComponent/Scene.h>

#include <EntityComponent/Entity.h>

Entity* Scene::CreateObject(const char* name)
{
	Entity* newEntity = new Entity(this);
	entitys.push_back(newEntity);
	newEntity->name = name;

	return newEntity;
}
