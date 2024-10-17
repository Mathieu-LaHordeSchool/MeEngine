#pragma once

#include <me/Core/Component.h>
#include <me/Core/ComponentsUI/UIElements.h>

#include <glm/glm.hpp>

class Texture;

class Image
	: public Component
	, public UIElement
{
	struct Internal;
	Internal* m_image;

public:
	GetComponentType(80001)

	explicit Image(class Entity* owner);
	~Image() noexcept = default;

	void Render(Renderer* render) override;

	glm::vec2 GetWindowSize() const;
	GetSetInternalValueHPP(Texture, Texture*)
};
