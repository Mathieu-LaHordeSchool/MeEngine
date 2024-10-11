
#include <glm/gtx/vector_angle.hpp>

#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/RendererObject/Renderer.h>
#include <Engine/Mesh/Mesh.h>
#include <Engine/EntityComponent/TransformData.h>

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

bool Camera::InFieldOfView(Mesh mesh, TransformData* trans, const glm::mat4& viewMatrix)
{
	glm::vec3 min, max;
	mesh.GetBoundsMesh(min, max);

	min += trans->GetWorldPosition() * (trans->GetWorldScale() / 2.f);
	max += trans->GetWorldPosition() * (trans->GetWorldScale() / 2.f);

	glm::vec4 point1 = glm::vec4(min, 1.0);
	glm::vec4 point2 = glm::vec4(max, 1.0);

	glm::vec4 transformedPoint1 = viewMatrix * point1;
	glm::vec4 transformedPoint2 = viewMatrix * point2;

	bool isInView1 = transformedPoint1.x >= -1.0f && transformedPoint1.x <= 1.0f &&
		transformedPoint1.y >= -1.0f && transformedPoint1.y <= 1.0f &&
		transformedPoint1.z >= -1.0f && transformedPoint1.z <= 1.0f;

	bool isInView2 = transformedPoint2.x >= -1.0f && transformedPoint2.x <= 1.0f &&
		transformedPoint2.y >= -1.0f && transformedPoint2.y <= 1.0f &&
		transformedPoint2.z >= -1.0f && transformedPoint2.z <= 1.0f;

	return isInView1 || isInView2;
}


GetSetInternalValueCPP(Fov, fov, float, Camera, m_camera)
GetSetInternalValueCPP(NearRender, zNear, float, Camera, m_camera)
GetSetInternalValueCPP(FarRender, zFar, float, Camera, m_camera)
