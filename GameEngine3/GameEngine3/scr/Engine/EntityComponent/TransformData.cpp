
#include <Engine/EntityComponent/TransformData.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TransformData::Internal
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.f);
};

TransformData::TransformData()
	: m_transform(new Internal())
	, name(""), parent(nullptr)
{}
TransformData::~TransformData() noexcept
{}

glm::vec3 TransformData::GetWorldPosition() const
{
	glm::vec3 position = m_transform->position;

	if (parent) {
		glm::vec3 ownToParent = (m_transform->position - parent->GetWorldPosition());
		return position + (parent->GetTransformForward() * ownToParent);
	}

	return position;
}
glm::vec3 TransformData::GetWorldRotation() const
{
	glm::vec3 rotation = m_transform->rotation;

	if (parent)
		return rotation + parent->GetLocalRotation();
}
glm::vec3 TransformData::GetWorldScale() const
{
	glm::vec3 scale = m_transform->scale;

	if (parent)
		return scale * parent->GetLocalScale();

	return scale;
}

glm::vec3 TransformData::GetLocalPosition() const
{
	return m_transform->position;
}
glm::vec3 TransformData::GetLocalRotation() const
{
	return m_transform->rotation;
}
glm::vec3 TransformData::GetLocalScale() const
{
	return m_transform->scale;
}

void TransformData::Translate(glm::vec3 axis, float value)
{
	m_transform->position += axis * value;
}
void TransformData::Rotate(glm::vec3 axis, float value)
{
	m_transform->rotation += axis * value;
}
void TransformData::Scale(glm::vec3 axis, float value)
{
	m_transform->scale += axis * value;
}

void TransformData::SetPosition(glm::vec3 pos)
{
	m_transform->position = pos;
}
void TransformData::SetRotation(glm::vec3 rot)
{
	m_transform->rotation = rot;
}
void TransformData::SetScale(glm::vec3 scale)
{
	m_transform->scale = scale;
}

glm::mat4 TransformData::GetTransformMatrix() const
{
	glm::mat4 matrix(1.f);
	glm::vec3 position = GetWorldPosition();
	glm::vec3 rotation = GetWorldRotation();
	glm::vec3 scale = GetWorldScale();

	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::translate(matrix, position);
	matrix = glm::scale(matrix, scale);

	return matrix;
}
glm::vec3 TransformData::GetTransformForward() const
{
	float yaw = m_transform->rotation.y;
	float pitch = m_transform->rotation.x;

	glm::vec3 forward;
	forward.x = cos(pitch) * sin(yaw);
	forward.y = sin(pitch);
	forward.z = cos(pitch) * cos(yaw);

	return glm::normalize(forward);
}
