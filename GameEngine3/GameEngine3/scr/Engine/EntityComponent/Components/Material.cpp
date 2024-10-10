
#include <Engine/EntityComponent/Components/Material.h>

#include <Engine/Texture/Texture.h>

struct Material::Internal
{
    Texture* albedo = new Texture("Ressources/Textures/ao_default.png");
    glm::vec4 color = glm::vec4(1.f);
};

Material::Material(Entity* owner)
	: Component(owner)
    , m_material(new Internal())
{
}

GetSetInternalValueCPP(AlbedoTexture, albedo, Texture*, Material, m_material)
GetSetInternalValueCPP(Color, color, glm::vec4, Material, m_material)
