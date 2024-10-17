#pragma once

#include <unordered_map>
#include <me/Core/EnableObject.h>

class Component;
class TransformData;
class Scene;

class Entity
	: public EnableObject
{
private:
	struct Internal;
	Internal* m_entity;

public:
	explicit Entity(class Scene* scn);
	~Entity() noexcept = default;

	TransformData* Transform();

	Component* AddComponent(Component* comp);
	Component* GetComponent(int comp);
	bool	   HasComponent(int comp);

	Scene* GetScene() const;
	void Render(class Renderer* render);
	void Start();
	void BindInputs(class Inputs* inputs);
	void Update();

	template<typename COMP>
	COMP* AddComponent() {
		return static_cast<COMP*>(AddComponent(new COMP(this)));
	}
	template<typename COMP>
	COMP* GetComponent() {
		return static_cast<COMP*>(GetComponent(COMP::GetStaticType()));
	}
	template<typename COMP>
	bool HasComponent() {
		return HasComponent(COMP::GetStaticType());
	}
};
