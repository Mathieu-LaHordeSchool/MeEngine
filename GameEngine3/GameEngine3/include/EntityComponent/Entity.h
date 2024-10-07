#pragma once

#include <unordered_map>
#include <EntityComponent/TransformData.h>

class Component;
class Scene;

class Entity 
	: public TransformData
{
private:
	Scene* ownScene;
	std::unordered_map<char*, Component*> components;

public:
	explicit Entity(Scene* scn) {
		ownScene = scn;
	}
	~Entity() noexcept = default;

	Component* AddComponent(Component* comp);
	Component* GetComponent(Component* comp);

	template<typename COMP>
	COMP* AddComponent() {
		return static_cast<COMP*>(AddComponent(new COMP(this)));
	}
	template<typename COMP>
	COMP* GetComponent() {
		return static_cast<COMP*>(GetComponent(new COMP(this)));
	}
};
