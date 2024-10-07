
#include <EntityComponent/TransformData.h>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 TransformData::GetTransformMatrix()
{
	glm::mat4 matrix(1.f);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::translate(matrix, position);
	matrix = glm::scale(matrix, scale);

	return matrix;
}
