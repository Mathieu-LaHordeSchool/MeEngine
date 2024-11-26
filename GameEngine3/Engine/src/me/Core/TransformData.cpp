
#include <iostream>
#include <ostream>
#include <me/Core/TransformData.h>
#include <me/Core/Entity.h>
#include <me/Core/UI/UIElements.h>

#include <glm/glm.hpp>
#include <vector>
#include <glm/detail/type_quat.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace me::core;

struct TransformData::Internal
{
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale = glm::vec3(1.f);
	glm::vec3 size;

	const char* name;
	TransformData* parent;
	Entity* owner;

	std::vector<TransformData*> children;

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
		glm::mat4 parentTransformMatrix = glm::mat4(1.f);
		parentTransformMatrix = glm::translate(parentTransformMatrix, m_transform->parent->GetWorldPosition());
		parentTransformMatrix = glm::rotate(parentTransformMatrix, m_transform->parent->GetWorldRotation().x, glm::vec3(1.f, 0.f, 0.f));
		parentTransformMatrix = glm::rotate(parentTransformMatrix, m_transform->parent->GetWorldRotation().y, glm::vec3(0.f, 1.f, 0.f));
		parentTransformMatrix = glm::rotate(parentTransformMatrix, m_transform->parent->GetWorldRotation().z, glm::vec3(0.f, 0.f, 1.f));

		glm::vec4 transformedPosition = parentTransformMatrix * glm::vec4(localPosition, 1.0f);
		return glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
	}
	
	return localPosition;
}
glm::quat TransformData::GetWorldRotation() const
{
	glm::quat rotation = m_transform->rotation;

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
glm::vec3 TransformData::GetWorldSize() const
{
	glm::vec3 size = m_transform->size;
	size = glm::vec3(size.x, size.y, 0.f);

	if (m_transform->parent)
		return size + m_transform->parent->GetLocalSize();

	return size;
}

glm::vec3 TransformData::GetLocalPosition() const
{
	return m_transform->position;
}
glm::quat TransformData::GetLocalRotation() const
{
	return m_transform->rotation;
}
glm::vec3 TransformData::GetLocalScale() const
{
	return m_transform->scale;
}
glm::vec3 TransformData::GetLocalSize() const
{
	glm::vec3 size = m_transform->size;
	return glm::vec3(size.x, size.y, 0.f);
}

void TransformData::Translate(const glm::vec3& axis, float value)
{
	m_transform->position += axis * value;
	DirtyMatrix();
}
void TransformData::Rotate(const glm::vec3& axis, float value)
{
	m_transform->rotation += glm::angleAxis(glm::radians(value), axis);
	DirtyMatrix();
}
void TransformData::Scale(const glm::vec3& axis, float value)
{
	m_transform->scale += axis * value;	
	DirtyMatrix();
}

void TransformData::SetLocalPosition(const glm::vec3& pos)
{
	if (pos == m_transform->position)
		return;
	
	m_transform->position = pos;
	DirtyMatrix();
}
void TransformData::SetLocalRotation(glm::quat rot)
{
	if (m_transform->rotation == rot)
		return;
	
	m_transform->rotation = rot;
	DirtyMatrix();
}
void TransformData::SetLocalScale(const glm::vec3& scale)
{
	if (scale == m_transform->scale)
		return;
	
	m_transform->scale = scale;
	DirtyMatrix();
}
void TransformData::SetLocalSize(const glm::vec3& size)
{
	if (size == m_transform->size)
		return;
	
	m_transform->size = size;
	DirtyMatrix();
}

void TransformData::SetWorldPosition(const glm::vec3& pos)
{
	if (pos == m_transform->position)
		return;
	
	if (m_transform->parent)
	{
		glm::mat4 parentMatrix = glm::inverse(m_transform->parent->GetTransformMatrix());
		glm::vec4 localPos = parentMatrix * glm::vec4(pos, 1.0f);
		SetLocalPosition(glm::vec3(localPos));
	}
	else
	{
		SetLocalPosition(pos);
	}

	DirtyMatrix();
}
void TransformData::SetWorldRotation(glm::quat rot)
{
	if (rot == m_transform->rotation)
		return;
	
	if (m_transform->parent)
	{
		glm::quat parentRot = m_transform->parent->GetWorldRotation();
		SetLocalRotation(rot - parentRot);
	}
	else
	{
		SetLocalRotation(rot);
	}

	DirtyMatrix();
}
void TransformData::SetWorldScale(const glm::vec3& scale)
{
	if (scale == m_transform->scale)
		return;
	
	if (m_transform->parent)
	{
		glm::vec3 parentScale = m_transform->parent->GetWorldScale();
		SetLocalScale(scale / parentScale);
	}
	else
	{
		SetLocalScale(scale);
	}
}
void TransformData::SetWorldSize(const glm::vec3& size)
{
	if (size == m_transform->size)
		return;
	
	if (m_transform->parent)
	{
		glm::vec3 parentScale = m_transform->parent->GetWorldSize();
		SetLocalSize(size / parentScale);
	}
	else
	{
		SetLocalSize(size);
	}
}

glm::mat4 TransformData::GetTransformMatrix() const
{
	if (!m_transform->needModelUpdate)
		return m_transform->model;

	glm::mat4 matrix(1.f);
	glm::vec3 position = GetWorldPosition();
	glm::quat rotation = GetWorldRotation();
	glm::vec3 scale = GetWorldScale();

	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.f, 0.f, 0.f));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.f, 1.f, 0.f));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.f, 0.f, 1.f));
	matrix = glm::translate(matrix, position);
	matrix = glm::scale(matrix, scale);

	m_transform->model = matrix;
	m_transform->needModelUpdate = false;
	
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

	if (trans)
		SetActive(trans->GetActive());
}
TransformData* TransformData::GetParent() const
{
	return m_transform->parent;
}
void TransformData::SetName(const char* name)
{
	m_transform->name = name;
}
const char* TransformData::GetName() const
{
	return m_transform->name;
}

void TransformData::SetOwner(Entity* owner)
{
	m_transform->owner = owner;
}
Entity* TransformData::GetOwner() const
{
	return m_transform->owner;
}

TransformData** TransformData::GetChildren() const
{
	return m_transform->children.data();
}
int TransformData::GetChildCount() const
{
	return m_transform->children.size();
}
void TransformData::AddChildren(TransformData* child) const
{
	m_transform->children.push_back(child);
}
void TransformData::RemoveChildren(const TransformData* child) const
{
	const auto& it = std::ranges::find(m_transform->children, child);

	if (it != m_transform->children.end()) {
		m_transform->children.erase(it);
	}
}

void TransformData::DirtyMatrix()
{
	m_transform->needModelUpdate = true;

	for (size_t i = 0; i < GetChildCount(); ++i) {
		GetChildren()[i]->DirtyMatrix();
	}
}
