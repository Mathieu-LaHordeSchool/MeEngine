
#include <iostream>
#include <glm/gtx/vector_angle.hpp>

#include <me/Core/Components/Render/Camera.h>
#include <me/Core/Entity.h>
#include <me/Render/Renderer.h>
#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/TransformData.h>

using namespace me::core::components::render;

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

void Camera::Render(me::render::Renderer* render)
{
	render->SetCamera(GetOwner());
}

bool Camera::InFieldOfView(me::core::render::Mesh mesh, me::core::TransformData* trans)
{
	glm::vec3 min, max;
	mesh.GetBoundsMesh(min, max);

	min += (trans->GetWorldPosition() - trans->GetWorldScale());
	max += (trans->GetWorldPosition() + trans->GetWorldScale());

	glm::vec3 fwd = GetOwner()->Transform()->GetTransformForward();
	glm::vec3 pos = GetOwner()->Transform()->GetWorldPosition();

	glm::vec3 minDir = glm::normalize(min - pos);
	glm::vec3 maxDir = glm::normalize(max - pos);

	float angleMin = cos(glm::angle(fwd, minDir));
	float angleMax = cos(glm::angle(fwd, maxDir));
	float angleFov = cos(glm::radians(m_camera->fov));

	if (angleFov < angleMin || angleFov < angleMax)
		return true;

	if (angleMin < 0.f && angleMax < 0.f)
		return false;

	if (angleFov > angleMax || angleFov > angleMin)
		return true;

	return false;
}


GetSetInternalValueCPP(Fov, fov, float, Camera, m_camera)
GetSetInternalValueCPP(NearRender, zNear, float, Camera, m_camera)
GetSetInternalValueCPP(FarRender, zFar, float, Camera, m_camera)
