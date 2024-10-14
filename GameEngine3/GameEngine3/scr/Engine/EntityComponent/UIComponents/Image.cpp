
#include <Engine/EntityComponent/UIComponents/Image.h>

#include <Engine/RendererObject/Renderer.h>
#include <Engine/Texture/Texture.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/Texture/Texture.h>
#include <Engine/Window/Window.h>

struct Image::Internal
{
	Texture* texture = new Texture("Ressources/Textures/ao_default.png");
	glm::vec2 windowSize;
};

Image::Image(Entity* owner)
	: Component(owner), m_image(new Internal())
{}

void Image::Render(Renderer* render)
{
	m_image->windowSize = render->GetWindow()->GetSize();
	render->PushUI(GetOwner()->Transform(), this, m_image->texture);
}

glm::vec2 Image::GetWindowSize() const
{
	return m_image->windowSize;
}
GetSetInternalValueCPP(Texture, texture, Texture*, Image, m_image)
