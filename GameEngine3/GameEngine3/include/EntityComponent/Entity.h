#pragma once

#include <unordered_map>

class Component;
class TransformData;

class Entity
{
private:
	struct Internal;
	Internal* m_entity;

public:
	explicit Entity(class Scene* scn);
	~Entity() noexcept = default;

	TransformData* Transform();

	Component* AddComponent(Component* comp);
	Component* GetComponent(Component* comp);
	void Render(class Renderer* render);

	template<typename COMP>
	COMP* AddComponent() {
		return static_cast<COMP*>(AddComponent(new COMP(this)));
	}
	template<typename COMP>
	COMP* GetComponent() {
		return static_cast<COMP*>(GetComponent(new COMP(this)));
	}
};