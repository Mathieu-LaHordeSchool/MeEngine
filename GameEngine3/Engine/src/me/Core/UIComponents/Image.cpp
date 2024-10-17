
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
	glm::vec2 windowSize;
};

Image::Image(Entity* owner)
	: Component(owner), m_image(new Internal())
{}

void Image::Render(me::render::Renderer* render)
{
	m_image->windowSize = render->GetWindow()->GetSize();
	render->PushImage(GetOwner()->Transform(), this, m_image->texture);
}

glm::vec2 Image::GetWindowSize() const
{
	return m_image->windowSize;
}
GetSetInternalValueCPP(Texture, texture, me::core::render::Texture*, Image, m_image)
