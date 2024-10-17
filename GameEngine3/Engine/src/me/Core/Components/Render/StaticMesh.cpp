
#include <me/Core/Components/Render/StaticMesh.h>

#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/TransformData.h>
#include <me/Core/Entity.h>
#include <me/Render/Renderer.h>

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
