
#include <iostream>

#include <Engine/RendererObject/Renderer.h>
#include <Engine/RendererObject/Shader/Shader.h>
#include <Engine/RendererObject/Shader/ShaderProgram.h>
#include <Engine/RendererObject/Buffer.h>
#include <Engine/RendererObject/VertexArray.h>
#include <Engine/RendererObject/RenderObjectData.h>
#include <Engine/Mesh/Mesh.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/Window/Window.h>
#include <Engine/Texture/Texture.h>

#include <Engine/EntityComponent/Components/StaticMesh.h>
#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Components/Material.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>

struct Renderer::Internal
{
	Window* window;

	std::vector<std::tuple<TransformData*, Material*, Mesh>> geometrys;
	Camera* camera;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	Shader* vsShader = new Shader("Ressources/Shaders/vertex.vert", EShaderType::Vertex);
	Shader* fsNoTextureShader = new Shader("Ressources/Shaders/fragmentNoTexture.frag", EShaderType::Fragment);
	Shader* fsTextureShader = new Shader("Ressources/Shaders/fragmentTexture.frag", EShaderType::Fragment);

	ShaderProgram* shaderProgramNoTexture = new ShaderProgram(vsShader, fsNoTextureShader);
	ShaderProgram* shaderProgramTexture = new ShaderProgram(vsShader, fsTextureShader);

	Buffer* vertexsBuffer = new Buffer();
	Buffer* normalsBuffer = new Buffer();
	Buffer* uvsBuffer = new Buffer();
	Buffer* elementsBuffer = new Buffer();

	VertexArrayObject* vao = new VertexArrayObject();
	RenderObjectData* bufferData = new RenderObjectData();
};

Renderer::Renderer(Window* window)
	: m_renderer(new Internal())
{
	m_renderer->vao->AttributeBinding(0, 0, 3, GL_FLOAT, GL_FALSE, 0); // for vertices
	m_renderer->vao->AttributeBinding(1, 1, 3, GL_FLOAT, GL_FALSE, 0); // for normals
	m_renderer->vao->AttributeBinding(2, 2, 2, GL_UNSIGNED_INT, GL_FALSE, 0); // for uvs

	m_renderer->window = window;

	glEnable(GL_DEPTH_TEST);
}

void Renderer::SetCamera(Entity* entity)
{
	if (entity->HasComponent<Camera>())
		m_renderer->camera = entity->GetComponent<Camera>();
}
void Renderer::PushGeometry(Entity* entity)
{
	StaticMesh* staticMesh = entity->GetComponent<StaticMesh>();
	Material* material = entity->GetComponent<Material>();

	if (material) {
		if (!material->GetActive())
			material = nullptr;
	}

	m_renderer->geometrys.push_back(std::make_tuple(entity->Transform(), material, staticMesh->GetMesh()));
}

void Renderer::ClearAllRendererData()
{
	m_renderer->geometrys.clear();
}

void Renderer::Execute()
{
	glClearColor(.1f, .2f, .3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& tuple : m_renderer->geometrys)
	{
		TransformData*	transform	= std::get<0>(tuple);
		Material*		material	= std::get<1>(tuple);
		Mesh			mesh		= std::get<2>(tuple);
		Camera*			cam			= m_renderer->camera;

		CalculViewMatrix(cam);
		CreateAndBindBuffers(mesh);

		if (!material)
			Draw(transform, mesh);
		else
			Draw(transform, material, mesh);
	}
}

void Renderer::CalculViewMatrix(Camera* cam)
{
	TransformData* trans = cam->GetOwner()->Transform();
	glm::vec3 camPos = trans->GetWorldPosition();
	glm::vec3 fwd = trans->GetTransformForward();
	glm::vec2 sizeWindow = m_renderer->window->GetSize();

	m_renderer->viewMatrix = glm::lookAt(
		camPos,
		fwd + camPos, // direction
		glm::vec3(0.f, 1.f, 0.f)  // vector up
	);

	float fov = cam->GetFov();
	float zNear = cam->GetNearRender();
	float zFar = cam->GetFarRender();

	m_renderer->projectionMatrix = glm::perspective(
		glm::radians(fov),
		sizeWindow.x / sizeWindow.y,
		zNear, zFar
	);
}

void Renderer::CreateAndBindBuffers(const Mesh& mesh)
{
	m_renderer->vertexsBuffer = m_renderer->bufferData->GetOrCreateVertexBuffer(mesh.Vertices);
	m_renderer->normalsBuffer = m_renderer->bufferData->GetOrCreateNormalBuffer(mesh.Normals);
	m_renderer->uvsBuffer = m_renderer->bufferData->GetOrCreateUvsBuffer(mesh.Uvs);
	m_renderer->elementsBuffer = m_renderer->bufferData->GetOrCreateElementBuffer(mesh.Elements);

	m_renderer->vao->BindElementBuffer(m_renderer->elementsBuffer);
	m_renderer->vao->BindingBuffer<float>(0, 0, m_renderer->vertexsBuffer, 3);
	m_renderer->vao->BindingBuffer<float>(1, 0, m_renderer->normalsBuffer, 3);
	m_renderer->vao->BindingBuffer<float>(2, 0, m_renderer->uvsBuffer, 2);
}

void Renderer::Draw(TransformData* trans, const Mesh& mesh)
{
	ShaderProgram* sp = m_renderer->shaderProgramNoTexture;
	VertexArrayObject* VAO = m_renderer->vao;

	sp->StartShaderProgram();
	VAO->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("uViewMatrix", m_renderer->viewMatrix);
	sp->SetMat4("uProjectionMatrix", m_renderer->projectionMatrix);
	sp->SetMat4("uModel", modelTrans);

	glDrawElements(GL_TRIANGLES, mesh.Vertices.size(), GL_UNSIGNED_INT, 0);

	VAO->UnbindVertexArray();
	sp->StopShaderProgram();
}
void Renderer::Draw(TransformData* trans, Material* material, const Mesh& mesh)
{
	ShaderProgram* sp = m_renderer->shaderProgramTexture;
	VertexArrayObject* VAO = m_renderer->vao;

	sp->StartShaderProgram();
	VAO->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("uViewMatrix", m_renderer->viewMatrix);
	sp->SetMat4("uProjectionMatrix", m_renderer->projectionMatrix);
	sp->SetMat4("uModel", modelTrans);

	material->GetAlbedoTexture()->BindTexture(GL_TEXTURE0);
	glm::vec4 color = material->GetColor();
	sp->SetSampler2D("albedoTexture", GL_TEXTURE0);
	sp->SetVec4("color", color);
	
	glDrawElements(GL_TRIANGLES, mesh.Vertices.size(), GL_UNSIGNED_INT, 0);

	VAO->UnbindVertexArray();
	sp->StopShaderProgram();
}
