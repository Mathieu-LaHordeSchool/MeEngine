#pragma once

#include <me/Core/Component.h>

class StaticMesh
	: public Component
{
	struct Internal;
	Internal* m_staticMesh;

public:
	GetComponentType(90003)

	explicit StaticMesh(class Entity* owner);
	~StaticMesh() noexcept = default;

	void Render(class Renderer* render) override;
	Component* Clone() override;

	void SetMesh(const class Mesh& mesh);
	class Mesh GetMesh() const;
};
