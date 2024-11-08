#pragma once

#include <me/Core/Component.h>

namespace me::core { class TransformData; }
namespace me::core::render { class Mesh; }

namespace me::core::components::render {
	class Camera
		: public Component
	{
		struct Internal;
		Internal* m_camera;

	public:
		GetComponentType("Camera")

			explicit Camera(class Entity* owner);
		~Camera() noexcept = default;

		void Render(me::render::Renderer* render) override;
		bool InFieldOfView(me::core::render::Mesh mesh, me::core::TransformData* trans);

		GetSetInternalValueHPP(Fov, float)
		GetSetInternalValueHPP(NearRender, float)
		GetSetInternalValueHPP(FarRender, float)
	};
}


