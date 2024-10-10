#pragma once

#include <Engine/EntityComponent/Component.h>
#include <glm/glm.hpp>

class Texture;

class Material
	: public Component
{
	struct Internal;
	Internal* m_material;

public:
	explicit Material(class Entity* owner);
	~Material() noexcept = default;

	const char* GetType() const override { return "MaterialComponentType"; }

	GetSetInternalValueHPP(AlbedoTexture, Texture*)
	GetSetInternalValueHPP(Color, glm::vec4)
};
