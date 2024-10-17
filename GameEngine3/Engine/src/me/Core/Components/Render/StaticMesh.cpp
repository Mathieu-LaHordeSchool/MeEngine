
#include <me/Core/Components/Render/StaticMesh.h>

#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/TransformData.h>
#include <me/Core/Entity.h>
#include <me/Render/Renderer.h>

using namespace me::core::components::render;

struct StaticMesh::Internal
{
	me::core::render::Mesh mesh;
};

StaticMesh::StaticMesh(me::core::Entity* owner)
	: Component(owner),
	m_staticMesh(new Internal())
{
}

void StaticMesh::Render(me::render::Renderer* render)
{
	render->PushGeometry(GetOwner());
}

void StaticMesh::SetMesh(const me::core::render::Mesh& mesh)
{
	m_staticMesh->mesh = mesh;
}

me::core::render::Mesh StaticMesh::GetMesh() const
{
	return m_staticMesh->mesh;
}
