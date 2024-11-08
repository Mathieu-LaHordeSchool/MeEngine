#pragma once

#include <me/Core/Component.h>
#include <glm/glm.hpp>

namespace me::core { class Entity; }
namespace me::core::render { class Texture; }

namespace me::core::components::render {

	class Material
		: public Component
	{
		struct Internal;
		Internal* m_material;

	public:
		GetComponentType("Material")

		explicit Material(me::core::Entity* owner);
		~Material() noexcept = default;

		GetSetInternalValueHPP(AlbedoTexture, me::core::render::Texture*)
		GetSetInternalValueHPP(Color, glm::vec4)
	};
}


