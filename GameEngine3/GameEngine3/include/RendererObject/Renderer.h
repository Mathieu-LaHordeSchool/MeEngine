#pragma once

#include <unordered_map>

class Entity;
class Mesh;

class Renderer 
{
public:
	std::unordered_map<Entity*, Mesh> geometry;

	void Render();
};
