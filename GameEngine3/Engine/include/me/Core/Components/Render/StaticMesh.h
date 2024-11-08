#pragma once

#include <me/Core/Component.h>

namespace me::core { class Entity; }
namespace me::core::render { class Mesh; }
namespace me::render { class Renderer; }

namespace me::core::components::render {
	class StaticMesh
		: public Component
	{
		struct Internal;
		Internal* m_staticMesh;

	public:
		GetComponentType("StaticMesh")

			explicit StaticMesh(me::core::Entity* owner);
		~StaticMesh() noexcept = default;

		void Render(me::render::Renderer* render) override;
		void SetMesh(const me::core::render::Mesh& mesh);
		me::core::render::Mesh GetMesh() const;
	};
}
