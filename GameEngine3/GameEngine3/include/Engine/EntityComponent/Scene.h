#pragma once

class Entity;
class HandleTimer;

class Scene
{
private:
	struct Internal;
	Internal* m_scene;

	void UpdateTimer();

public:
	explicit Scene();
	~Scene() noexcept = default;

	Entity* CreateObject(const char* name);
	HandleTimer GetHandleTimer() const;

	void Start();
	void Update();

	void Render(class Renderer* render);
};
