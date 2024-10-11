
#include <Engine/EntityComponent/TransformData.h>

#include <Engine/EntityComponent/Entity.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TransformData::Internal
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.f);

	const char* name;
	TransformData* parent;
	Entity* owner;

	glm::mat4 model;
	bool needModelUpdate = true;
};

TransformData::TransformData()
	: m_transform(new Internal())
{}
TransformData::~TransformData() noexcept
{}

glm::vec3 TransformData::GetWorldPosition() const
{
	glm::vec3 localPosition = GetLocalPosition();

	if (m_transform->parent) {
		glm::mat4 parentTransformMatrix = m_transform->parent->GetTransformMatrix();
		glm::vec4 transformedPosition = parentTransformMatrix * glm::vec4(localPosition, 1.0f);
		return glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
	}

	// Si pas de parent, retourner simplement la position locale
	return localPosition;
}
glm::vec3 TransformData::GetWorldRotation() const
{
	glm::vec3 rotation = m_transform->rotation;

	if (m_transform->parent)
		return rotation + m_transform->parent->GetLocalRotation();

	return rotation;
}
glm::vec3 TransformData::GetWorldScale() const
{
	glm::vec3 scale = m_transform->scale;

	if (m_transform->parent)
		return scale * m_transform->parent->GetLocalScale();

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

void TransformData::Translate(const glm::vec3& axis, float value)
{
	m_transform->position += axis * value;
}
void TransformData::Rotate(const glm::vec3& axis, float value)
{
	m_transform->rotation += axis * value;
}
void TransformData::Scale(const glm::vec3& axis, float value)
{
	m_transform->scale += axis * value;
}

void TransformData::SetLocalPosition(const glm::vec3& pos)
{
	m_transform->position = pos;
}
void TransformData::SetLocalRotation(const glm::vec3& rot)
{
	m_transform->rotation = rot;
}
void TransformData::SetLocalScale(const glm::vec3& scale)
{
	m_transform->scale = scale;
}

void TransformData::SetWorldPosition(const glm::vec3& pos)
{
	glm::vec3 parentPos = m_transform->parent ? m_transform->parent->GetWorldPosition() : glm::vec3(0.f);
	SetLocalPosition(pos - parentPos);
}
void TransformData::SetWorldRotation(const glm::vec3& rot)
{
	glm::vec3 parentRot = m_transform->parent ? m_transform->parent->GetWorldRotation() : glm::vec3(0.f);
	SetLocalRotation(rot - parentRot);
}
void TransformData::SetWorldScale(const glm::vec3& scale)
{
	glm::vec3 parentScl = m_transform->parent ? m_transform->parent->GetWorldScale() : glm::vec3(0.f);
	SetLocalScale(scale - parentScl);
}

glm::mat4 TransformData::GetTransformMatrix() const
{
	glm::mat4 matrix(1.f);
	glm::vec3 position = GetWorldPosition();
	glm::vec3 rotation = GetWorldRotation();
	glm::vec3 scale = GetWorldScale();

	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::scale(matrix, scale);

	return matrix;
}

glm::vec3 TransformData::GetTransformForward() const
{
	float yaw = GetWorldRotation().y;
	float pitch = GetWorldRotation().x;

	glm::vec3 forward;
	forward.x = cos(pitch) * sin(yaw);
	forward.y = sin(pitch);
	forward.z = cos(pitch) * cos(yaw);

	return glm::normalize(forward);
}
glm::vec3 TransformData::GetTransformRight() const
{
	glm::vec3 fwd = GetTransformForward();
	return glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), fwd));
}
glm::vec3 TransformData::GetTransformUp() const
{
	glm::vec3 right = GetTransformRight();
	glm::vec3 fwd = GetTransformForward();

	return glm::normalize(glm::cross(right, fwd));
}

void TransformData::SetParent(TransformData* trans)
{
	m_transform->parent = trans;
}
void TransformData::SetName(const char* name)
{
	m_transform->name = name;
}

void TransformData::SetOwner(Entity* owner)
{
	m_transform->owner = owner;
}
Entity* TransformData::GetOwner() const
{
	return m_transform->owner;
}

TransformData* TransformData::Clone() const
{
	TransformData* cln = new TransformData();
	cln->m_transform = m_transform;

	return cln;
}
