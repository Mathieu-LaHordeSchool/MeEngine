#pragma once

#include <glm/glm.hpp>

class TransformData
{
public:
	const char* name;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.f);

	glm::mat4 GetTransformMatrix() const;
};
