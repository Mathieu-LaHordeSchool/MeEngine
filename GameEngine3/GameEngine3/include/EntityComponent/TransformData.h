#pragma once

#include <glm/glm.hpp>

class TransformData
{
public:
	const char* name;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 GetTransformMatrix();
};
