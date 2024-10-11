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
	GetComponentType(90002)

	explicit Material(class Entity* owner);
	~Material() noexcept = default;

	Component* Clone() override;

	GetSetInternalValueHPP(AlbedoTexture, Texture*)
	GetSetInternalValueHPP(Color, glm::vec4)
};
