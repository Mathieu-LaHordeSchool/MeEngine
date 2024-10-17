#pragma once

#include <me/Core/Component.h>
#include <me/Core/UI/UIElements.h>

#include <glm/glm.hpp>

namespace me::core::render { class Texture; }
namespace me::core { class Entity; }
namespace me::render { class Renderer; }

namespace me::core::components::ui {
	class Image
		: public Component
		, public me::core::ui::UIElement
	{
		struct Internal;
		Internal* m_image;

	public:
		GetComponentType(80001)

		explicit Image(me::core::Entity* owner);
		~Image() noexcept = default;

		void Render(me::render::Renderer* render) override;

		glm::vec2 GetWindowSize() const;
		GetSetInternalValueHPP(Texture, me::core::render::Texture*)
	};
}
