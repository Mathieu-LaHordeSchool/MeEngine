#pragma once

#include <Engine/EntityComponent/Component.h>

class Camera
	: public Component
{
	struct Internal;
	Internal* m_camera;

public:
	GetComponentType(90001)

	explicit Camera(class Entity* owner);
	~Camera() noexcept = default;

	void Render(Renderer* render) override;
	Component* Clone() override;

	bool InFieldOfView(class Mesh mesh, class TransformData* trans);

	GetSetInternalValueHPP(Fov, float)
	GetSetInternalValueHPP(NearRender, float)
	GetSetInternalValueHPP(FarRender, float)
};
