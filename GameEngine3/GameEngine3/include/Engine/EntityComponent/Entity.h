#pragma once

#include <unordered_map>

class Component;
class TransformData;
class Scene;

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
		return static_cast<COMP*>(GetComponent(new COMP(this)));
	}
};
