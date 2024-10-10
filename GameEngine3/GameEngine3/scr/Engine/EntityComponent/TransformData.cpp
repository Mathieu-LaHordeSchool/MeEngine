
#include <Engine/EntityComponent/TransformData.h>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 TransformData::GetTransformMatrix() const
{
	glm::mat4 matrix(1.f);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::translate(matrix, position);
	matrix = glm::scale(matrix, scale);

	return matrix;
}

glm::vec3 TransformData::GetTransformForward() const
{
	// Assumons que rotation est en radians (glm utilise généralement des radians)
	float yaw = rotation.y;
	float pitch = rotation.x;

	// Calcul du vecteur forward en utilisant les angles de yaw (Y) et pitch (X)
	glm::vec3 forward;
	forward.x = cos(pitch) * sin(yaw);
	forward.y = sin(pitch);
	forward.z = cos(pitch) * cos(yaw);

	// Normaliser le vecteur pour qu'il soit unitaire
	return glm::normalize(forward);
}
