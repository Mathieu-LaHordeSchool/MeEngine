#pragma once

#include <glm/glm.hpp>

namespace me::core::ui
{
	class UIElement;
}

namespace me::core {
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
		glm::quat GetWorldRotation() const;
		glm::vec3 GetWorldScale() const;
		glm::vec3 GetWorldSize() const;

		glm::vec3 GetLocalPosition() const;
		glm::quat GetLocalRotation() const;
		glm::vec3 GetLocalScale() const;
		glm::vec3 GetLocalSize() const;

		void Translate(const glm::vec3&, float value);
		void Rotate(const glm::vec3&, float value);
		void Scale(const glm::vec3&, float value);

		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalRotation(glm::quat rot);
		void SetLocalScale(const glm::vec3& scale);
		void SetLocalSize(const glm::vec3& size);

		void SetWorldPosition(const glm::vec3& pos);
		void SetWorldRotation(glm::quat rot);
		void SetWorldScale(const glm::vec3& scale);
		void SetWorldSize(const glm::vec3& size);

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

		TransformData** GetChildren() const;
		int GetChildCount() const;
		void AddChildren(TransformData* child) const;
		void RemoveChildren(const TransformData* child) const;

		void DirtyMatrix();
	};
}


