#pragma once

#include <functional>

class Entity;
class HandleTimer;
class TransformData;

class Scene
{
private:
	struct Internal;
	Internal* m_scene;

	void UpdateTimer();
	void LoopOnEntity(std::function<void(Entity*)> func);

public:
	explicit Scene();
	~Scene() noexcept = default;

	Entity* CreateObject(const char* name, TransformData* parent = nullptr);
	HandleTimer GetHandleTimer() const;

	void Start();
	void BindInput(class Inputs* inputs);
	void Update();

	void Render(class Renderer* render);
};
