#pragma once

#include <vector>

class Entity;

class Scene
{
private:
	std::vector<Entity*> entitys;

public:
	Entity* CreateObject(const char* name);
};
