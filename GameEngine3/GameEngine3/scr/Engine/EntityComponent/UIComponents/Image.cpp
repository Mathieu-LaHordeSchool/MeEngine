
#include <Engine/EntityComponent/UIComponents/Image.h>

#include <Engine/RendererObject/Renderer.h>
#include <Engine/Texture/Texture.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/Texture/Texture.h>

struct Image::Internal
{
	Texture* texture = new Texture("Ressources/Textures/ao_default.png");
};

Image::Image(Entity* owner)
	: Component(owner), m_image(new Internal())
{
}

void Image::Render(Renderer* render)
{
	render->PushUI(GetOwner()->Transform(), this, m_image->texture);
}

GetSetInternalValueCPP(Texture, texture, Texture*, Image, m_image)
