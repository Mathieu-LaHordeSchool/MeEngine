
#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/RendererObject/Renderer.h>

Camera::Camera(Entity* owner)
	: Component(owner)
{
	this->width = 700.f;
	this->height = 500.f;

	this->zNear = 0.1f;
	this->zFar = 1000.f;
	this->fov = 90.f;
}

void Camera::Render(Renderer* render)
{
	render->PushCamera(*this);
}

void Camera::SetRenderCameraSize(float h, float w)
{
	width = w;
	height = h;
}
void Camera::SetRenderCameraDistance(float near, float far)
{
	zNear = near;
	zFar = far;
}
void Camera::SetRenderCmaeraFov(float fov)
{
	this->fov = fov;
}
