
#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/RendererObject/Renderer.h>

struct Camera::Internal
{
	float zNear = .1f;
	float zFar = 1000.f;
	float fov = 90.f;
};

Camera::Camera(Entity* owner)
	: Component(owner)
	, m_camera(new Internal())
{
}

void Camera::Render(Renderer* render)
{
	render->SetCamera(GetOwner());
}
Component* Camera::Clone()
{
	Camera* cln = new Camera(GetOwner());
	cln->m_camera = m_camera;

	return cln;
}

GetSetInternalValueCPP(Fov, fov, float, Camera, m_camera)
GetSetInternalValueCPP(NearRender, zNear, float, Camera, m_camera)
GetSetInternalValueCPP(FarRender, zFar, float, Camera, m_camera)
