
#include <me/Core/Components/Render/Material.h>

#include <me/Core/Render/Texture/Texture.h>

using namespace me::core::components::render;

struct Material::Internal
{
    me::core::render::Texture* albedo = new me::core::render::Texture("../Ressources/Textures/ao_default.png");
    glm::vec4 color = glm::vec4(1.f);
};

Material::Material(Entity* owner)
	: Component(owner)
    , m_material(new Internal())
{
}

GetSetInternalValueCPP(AlbedoTexture, albedo, me::core::render::Texture*, Material, m_material)
GetSetInternalValueCPP(Color, color, glm::vec4, Material, m_material)
