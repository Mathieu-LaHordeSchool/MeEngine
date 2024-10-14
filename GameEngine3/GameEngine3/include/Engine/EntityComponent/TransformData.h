#pragma once

#include <glm/glm.hpp>

class Entity;

class TransformData
{
private:
	struct Internal;
	Internal* m_transform;

public:
	explicit TransformData();
	~TransformData() noexcept;

	glm::vec3 GetWorldPosition() const;
	glm::vec3 GetWorldRotation() const;
	glm::vec3 GetWorldScale() const;

	glm::vec3 GetLocalPosition() const;
	glm::vec3 GetLocalRotation() const;
	glm::vec3 GetLocalScale() const;

	void Translate(const glm::vec3&, float value);
	void Rotate(const glm::vec3&, float value);
	void Scale(const glm::vec3&, float value);

	void SetLocalPosition(const glm::vec3& pos);
	void SetLocalRotation(const glm::vec3& rot);
	void SetLocalScale(const glm::vec3& scale);

	void SetWorldPosition(const glm::vec3& pos);
	void SetWorldRotation(const glm::vec3& rot);
	void SetWorldScale(const glm::vec3& scale);

	glm::mat4 GetTransformMatrix() const;

	glm::vec3 GetTransformForward() const;
	glm::vec3 GetTransformRight() const;
	glm::vec3 GetTransformUp() const;

	void SetParent(TransformData* trans);
	TransformData* GetParent() const;

	void SetName(const char* name);
	const char* GetName() const;

	void SetOwner(Entity* owner);
	Entity* GetOwner() const;

	TransformData* Clone() const;
};
