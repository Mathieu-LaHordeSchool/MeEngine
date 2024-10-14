#pragma once

#include <Engine/EntityComponent/Component.h>
#include <Engine/EntityComponent/UIComponents/UIElements.h>

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

	GetSetInternalValueHPP(Texture, Texture*)
};
