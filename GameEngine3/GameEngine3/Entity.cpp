
#include <EntityComponent/Entity.h>

#include <EntityComponent/Component.h>

Component* Entity::AddComponent(Component* comp)
{
	components[comp->GetType()] = comp;
}
Component* Entity::GetComponent(Component* comp)
{
	return components[comp->GetType()];
}
