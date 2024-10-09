
#include <EntityComponent/Components/StaticMesh.h>

#include <Mesh/Mesh.h>
#include <RendererObject/Renderer.h>
#include <EntityComponent/TransformData.h>
#include <EntityComponent/Entity.h>

struct StaticMesh::Internal
{
	Mesh mesh;
};

StaticMesh::StaticMesh(Entity* owner)
	: Component(owner),
	m_staticMesh(new Internal())
{
}

void StaticMesh::Render(Renderer* render)
{
	render->PushGeometry(*owner->Transform(), m_staticMesh->mesh);
}

void StaticMesh::SetMesh(const Mesh& mesh)
{
	m_staticMesh->mesh = mesh;
}
