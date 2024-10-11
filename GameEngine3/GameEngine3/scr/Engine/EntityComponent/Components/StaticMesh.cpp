
#include <Engine/EntityComponent/Components/StaticMesh.h>
#include <Engine/Mesh/Mesh.h>
#include <Engine/RendererObject/Renderer.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/EntityComponent/Entity.h>

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
	render->PushGeometry(GetOwner());
}

Component* StaticMesh::Clone()
{
	StaticMesh* cln = new StaticMesh(GetOwner());
	cln->m_staticMesh = m_staticMesh;

	return cln;
}

void StaticMesh::SetMesh(const Mesh& mesh)
{
	m_staticMesh->mesh = mesh;
}

Mesh StaticMesh::GetMesh() const
{
	return m_staticMesh->mesh;
}
