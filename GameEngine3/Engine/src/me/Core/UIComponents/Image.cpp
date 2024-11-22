
#include <me/Core/Components/UI/Image.h>

#include <me/Render/Renderer.h>
#include <me/Core/Render/Texture/Texture.h>
#include <me/Core/Entity.h>
#include <me/Core/TransformData.h>
#include <me/Render/Window/Window.h>

using namespace me::core::components::ui;

struct Image::Internal
{
	me::core::render::Texture* texture = new me::core::render::Texture("../Ressources/Textures/ao_default.png");
};

Image::Image(Entity* owner)
	: Component(owner), m_image(new Internal())
{}

void Image::Render(me::render::Renderer* render)
{
	render->PushImage(GetOwner(), this, m_image->texture);
}

GetSetInternalValueCPP(Texture, texture, me::core::render::Texture*, Image, m_image)
