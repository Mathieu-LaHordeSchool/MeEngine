#pragma once


#include <glm/glm.hpp>

class TransformData
{
private:
	struct Internal;
	Internal* m_transform;

public:
	explicit TransformData();
	~TransformData() noexcept;

	const char* name;
	TransformData* parent;

	glm::vec3 GetWorldPosition() const;
	glm::vec3 GetWorldRotation() const;
	glm::vec3 GetWorldScale() const;

	glm::vec3 GetLocalPosition() const;
	glm::vec3 GetLocalRotation() const;
	glm::vec3 GetLocalScale() const;

	void Translate(glm::vec3 axis, float value);
	void Rotate(glm::vec3 axis, float value);
	void Scale(glm::vec3 axis, float value);

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	glm::mat4 GetTransformMatrix() const;
	glm::vec3 GetTransformForward() const;
};
