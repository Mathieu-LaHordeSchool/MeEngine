#pragma once

#include <Engine/EntityComponent/Component.h>

class StaticMesh
	: public Component
{
	struct Internal;
	Internal* m_staticMesh;

public:
	explicit StaticMesh(class Entity* owner);
	~StaticMesh() noexcept = default;

	const char* GetType() const override {
		return "StaticMeshTypeComponent";
	}
	void Render(class Renderer* render) override;

	void SetMesh(const class Mesh& mesh);
	class Mesh GetMesh() const;
};
